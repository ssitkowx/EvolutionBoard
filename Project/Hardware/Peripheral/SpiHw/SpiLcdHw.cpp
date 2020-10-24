///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <memory.h>
#include "GpioHw.h"
#include "LoggerHw.h"
#include "Settings.h"
#include "SpiLcdHw.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

spi_device_handle_t SpiLcdHw::handle;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static void beforeTransfer (spi_transaction_t * v_transaction)
{
    int dcPin = (int)v_transaction->user;
    gpio_set_level (static_cast<gpio_num_t>(GpioHw::ELcd::eDc), dcPin);
}

SpiLcdHw::SpiLcdHw () : SpiHw (&handle)
{
    LOG (MODULE, "Init.");

    static spi_bus_config_t busConfig;
    busConfig.miso_io_num       = static_cast<int> (GpioHw::ELcd::eSdi);
    busConfig.mosi_io_num       = static_cast<int> (GpioHw::ELcd::eSdo);
    busConfig.sclk_io_num       = static_cast<int> (GpioHw::ELcd::eSck);
    busConfig.quadwp_io_num     = -1;
    busConfig.quadhd_io_num     = -1;
    busConfig.max_transfer_sz   = Settings::GetInstance ().Lcd.LinesPerTransfer * Settings::GetInstance ().Lcd.Width * TWO + EIGHT_BYTES;

    static spi_device_interface_config_t deviceConfig;
    deviceConfig.clock_speed_hz = 26*1000*1000;    // Clock out at 26 MHz
    deviceConfig.mode           = static_cast<uint8_t>(EMode::eCmd);
    deviceConfig.spics_io_num   = static_cast<int>    (GpioHw::ELcd::eCs);
    deviceConfig.queue_size     = SEVEN;
    deviceConfig.pre_cb         = beforeTransfer;

    esp_err_t status            = spi_bus_initialize (host, &busConfig, dmaChannel);
    ESP_ERROR_CHECK (status);

    status                      = spi_bus_add_device (host, &deviceConfig, &handle);
    ESP_ERROR_CHECK (status);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
