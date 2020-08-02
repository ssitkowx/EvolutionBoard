///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <memory.h>
#include "GpioHw.h"
#include "LoggerHw.h"
#include "Settings.h"
#include "SpiTouchHw.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

spi_device_handle_t SpiTouchHw::spi;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

SpiTouchHw::SpiTouchHw ()
{
    LOG (MODULE, "Init.");

    static spi_bus_config_t busCfg;
    busCfg.miso_io_num     = static_cast<int> (GpioHw::ETouch::eDin);
    busCfg.mosi_io_num     = static_cast<int> (GpioHw::ETouch::eDo);
    busCfg.sclk_io_num     = static_cast<int> (GpioHw::ETouch::eClk);
    busCfg.quadwp_io_num   = -1;
    busCfg.quadhd_io_num   = -1;
    busCfg.max_transfer_sz = THIRTY_TWO_BYTES;

    static spi_device_interface_config_t devCfg;
    //.clock_speed_hz=26*1000*1000,                 // Clock out at 26 MHz
    devCfg.clock_speed_hz  = ONE_HUNDRED_TWENTY_FIVE * 100;      // Clock out at 125 kHz
    devCfg.mode            = static_cast<uint8_t>(EMode::eCmd);
    devCfg.spics_io_num    = static_cast<int>    (GpioHw::ETouch::eCs);
    devCfg.queue_size      = FIVE;

    esp_err_t status       = spi_bus_initialize (touchHost, &busCfg, dmaChan);
    ESP_ERROR_CHECK (status);

    status                 = spi_bus_add_device (touchHost, &devCfg, &spi);
    ESP_ERROR_CHECK (status);
}

static uint8_t getFlag (SpiTouchHw::EFlag v_flag)
{
    if (v_flag == SpiTouchHw::EFlag::eDummy) { return ZERO; }
    return (ONE << static_cast<uint8_t> (v_flag));
}


void SpiTouchHw::Send (const uint8_t * const v_data, const uint16_t v_len)
{
    if (v_len == ZERO) { LOGE (MODULE, "Data length is empty."); return; }

    spi_transaction_t transaction;
    memset (&transaction, ZERO, sizeof (transaction));

    uint8_t flags = getFlag (static_cast<SpiTouchHw::EFlag>(v_data [FIRST_BYTE]));
    uint8_t user  = v_data [SECOND_BYTE];

    transaction.flags  = flags;
    transaction.user   = reinterpret_cast<void *>(user);
    transaction.length = v_len * EIGHT_BITS;

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

uint16_t SpiTouchHw::Receive (uint8_t * v_data)
{
    static spi_transaction_t transaction;
    memset (&transaction, ZERO, sizeof (transaction));

    transaction.flags  = getFlag (static_cast<SpiTouchHw::EFlag>(v_data [FIRST_BYTE]));
    transaction.user   = reinterpret_cast<void *>(v_data [SECOND_BYTE]);
    transaction.length = v_data [THIRD_BYTE] * EIGHT_BITS;

    esp_err_t status = spi_device_polling_transmit (spi, &transaction);
    assert (status == ESP_OK);

    v_data [FOURTH_BYTE] = transaction.rx_data [FIRST_BYTE];
    return transaction.length;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
