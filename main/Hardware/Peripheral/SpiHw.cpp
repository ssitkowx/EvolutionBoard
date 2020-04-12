///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <memory.h>
#include "SpiHw.h"
#include "Settings.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

spi_device_handle_t SpiHw::spi;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static void beforeTransfer (spi_transaction_t * v_transaction)
{
    int dcPin = (int)v_transaction->user;
    gpio_set_level (static_cast <gpio_num_t>(Gpio::EPinNum::eDc), dcPin);
}

SpiHw::SpiHw ()
{
    printf ("SpiHw init.\n");

    static spi_bus_config_t busCfg;
    busCfg.miso_io_num     = static_cast<int> (Gpio::EPinNum::eMiso);
    busCfg.mosi_io_num     = static_cast<int> (Gpio::EPinNum::eMosi);
    busCfg.sclk_io_num     = static_cast<int> (Gpio::EPinNum::eClk);
    busCfg.quadwp_io_num   = -1;
    busCfg.quadhd_io_num   = -1;
    busCfg.max_transfer_sz = Settings::GetInstance ().Lcd.MaxLinesPerTransfer * Settings::GetInstance ().Lcd.Length * 2 + 8;

    static spi_device_interface_config_t devCfg;
    //.clock_speed_hz=26*1000*1000,                 // Clock out at 26 MHz
    devCfg.clock_speed_hz  = 10*1000*1000;          // Clock out at 10 MHz
    devCfg.mode            = 0;
    devCfg.spics_io_num    = static_cast<int> (Gpio::EPinNum::eCs);
    devCfg.queue_size      = 7;
    devCfg.pre_cb          = beforeTransfer;

    esp_err_t status       = spi_bus_initialize (lcdHost, &busCfg, dmaChan);
    ESP_ERROR_CHECK (status);

    status                 = spi_bus_add_device (lcdHost, &devCfg, &spi);
    ESP_ERROR_CHECK (status);
}

uint8_t * SpiHw::Send (const uint8_t * v_data, const uint16_t v_len)
{
    if (v_len == 0)
    {
        assert (v_len == 0);
        return NULL;
    }

    static spi_transaction_t transaction;
    memset (&transaction, 0, sizeof (transaction));
    uint8_t flags = v_data [0];
    uint8_t user  = v_data [1];

    transaction.length = v_len * 8;
    transaction.user   = reinterpret_cast<void *>(user);

    if (v_data[0] == SPI_TRANS_USE_TXDATA)
    {
        transaction.flags       = flags;
        transaction.tx_data [0] = v_data [2];
        if (user == 1)
        {
            transaction.tx_data [1] = v_data [3];
            transaction.tx_data [2] = v_data [4];
            transaction.tx_data [3] = v_data [5];
        }
    }
    else
    {
        transaction.flags     = flags;
        transaction.tx_buffer = &v_data [2];
    }

    esp_err_t status = spi_device_polling_transmit (spi, &transaction);
    assert (status == ESP_OK);

    return transaction.rx_data;
}

void SpiHw::Send16Bits (const uint16_t * v_data, const uint16_t v_len)
{
    if (v_len == 0)
    {
        assert (v_len == 0);
        return;
    }

    spi_transaction_t transaction;
    memset (&transaction, 0, sizeof (transaction));

    transaction.flags     = 0;
    transaction.length    = v_len * 8 * 2;
    transaction.user      = (void *)1;
    transaction.tx_buffer = v_data;

    esp_err_t status = spi_device_polling_transmit (spi, &transaction);
    assert (status == ESP_OK);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
