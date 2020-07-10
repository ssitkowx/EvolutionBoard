///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "SpiHw.h"
#include <memory.h>
#include "GpioHw.h"
#include "LoggerHw.h"
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
    gpio_set_level (static_cast <gpio_num_t>(GpioHw::EPinNum::eDc), dcPin);
}

SpiHw::SpiHw ()
{
    LOG (MODULE, "Init /n");

    static spi_bus_config_t busCfg;
    busCfg.miso_io_num     = static_cast<int> (GpioHw::EPinNum::eMiso);
    busCfg.mosi_io_num     = static_cast<int> (GpioHw::EPinNum::eMosi);
    busCfg.sclk_io_num     = static_cast<int> (GpioHw::EPinNum::eClk);
    busCfg.quadwp_io_num   = -1;
    busCfg.quadhd_io_num   = -1;
    busCfg.max_transfer_sz = Settings::GetInstance ().Lcd.MaxLinesPerTransfer * Settings::GetInstance ().Lcd.Width;

    static spi_device_interface_config_t devCfg;
    //.clock_speed_hz=26*1000*1000,                 // Clock out at 26 MHz
    devCfg.clock_speed_hz  = 10*1000*1000;          // Clock out at 10 MHz
    devCfg.mode            = ZERO;
    devCfg.spics_io_num    = static_cast<int> (GpioHw::EPinNum::eCs);
    devCfg.queue_size      = SEVEN;
    devCfg.pre_cb          = beforeTransfer;

    esp_err_t status       = spi_bus_initialize (lcdHost, &busCfg, dmaChan);
    ESP_ERROR_CHECK (status);

    status                 = spi_bus_add_device (lcdHost, &devCfg, &spi);
    ESP_ERROR_CHECK (status);
}

static uint8_t getFlag (SpiHw::EFlag v_flag)
{
    if (v_flag == SpiHw::EFlag::eDummy) { return 0; }
    return (ONE << static_cast<uint8_t> (v_flag));
}


void SpiHw::Send (const uint8_t * const v_data, const uint16_t v_len)
{
    if (v_len == ZERO) { assert (v_len == ZERO); }

    static spi_transaction_t transaction;
    memset (&transaction, ZERO, sizeof (transaction));

    uint8_t flags = getFlag (static_cast<SpiHw::EFlag>(v_data [FIRST_BYTE]));
    uint8_t user  = v_data [SECOND_BYTE];

    transaction.length = v_len * EIGHT_BITS;
    transaction.user   = reinterpret_cast<void *>(user);
    transaction.flags  = flags;

    if (flags == SPI_TRANS_USE_TXDATA)
    {
        transaction.tx_data [FIRST_BYTE] = v_data [THIRD_BYTE];
        if (user == ONE)
        {
            transaction.tx_data [SECOND_BYTE] = v_data [FOURTH_BYTE];
            transaction.tx_data [THIRD_BYTE]  = v_data [FIFTH_BYTE];
            transaction.tx_data [FOURTH_BYTE] = v_data [SIXTH_BYTE];
        }
    }
    else
    {
        transaction.tx_buffer = &v_data [THIRD_BYTE];
    }

    esp_err_t status = spi_device_polling_transmit (spi, &transaction);
    assert (status == ESP_OK);
}

void SpiHw::Send (const uint16_t * const v_data, const uint16_t v_len)
{

    if (v_len == ZERO) { LOGE (MODULE, "Data length is empty.\n"); return; }

    spi_transaction_t transaction;
    memset (&transaction, ZERO, sizeof (transaction));

    transaction.flags     = 0;
    transaction.length    = v_len * EIGHT_BITS * TWO;
    transaction.user      = (void *)true;
    transaction.tx_buffer = v_data;

    esp_err_t status = spi_device_polling_transmit (spi, &transaction);
    assert (status == ESP_OK);
}

uint16_t SpiHw::Receive (uint8_t * v_data, const uint16_t v_len)
{
    spi_transaction_t transaction;
    memset (&transaction, ZERO, sizeof (transaction));

    transaction.flags     = ZERO;
    transaction.length    = v_len * EIGHT_BITS;
    transaction.user      = (void *)true;
    transaction.tx_buffer = v_data;

    esp_err_t status = spi_device_polling_transmit (spi, &transaction);
    assert (status == ESP_OK);

    v_data = transaction.rx_data;
    return ZERO;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
