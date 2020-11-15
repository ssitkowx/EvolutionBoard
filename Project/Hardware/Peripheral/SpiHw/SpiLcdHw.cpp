///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include <memory.h>
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

SpiLcdHw::SpiLcdHw (Gpio<GpioHw> & v_gpio) : SpiHw (&handle), gpio (v_gpio)
{
    LOG (MODULE, "Init.");

    // Initialize non-SPI GPIOs
    gpio.SetPinDirection (static_cast<uint16_t> (GpioHw::ELcd::eDc) , static_cast<uint16_t> (GpioHw::EPinMode::eOutput));
    gpio.SetPinDirection (static_cast<uint16_t> (GpioHw::ELcd::eRst), static_cast<uint16_t> (GpioHw::EPinMode::eOutput));

    //Reset the display
    gpio.SetPinLevel  (static_cast<uint16_t> (GpioHw::ELcd::eRst), false);
    Rtos::GetInstance ()->DelayInMs (ONE_HUNDRED);
    gpio.SetPinLevel  (static_cast<uint16_t> (GpioHw::ELcd::eRst), true);
    Rtos::GetInstance ()->DelayInMs (ONE_HUNDRED);

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
