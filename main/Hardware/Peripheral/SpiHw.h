#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Spi.h"
#include "Display.h"
#include "esp_err.h"
#include "driver/spi_master.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class SpiHw final: public Spi
{
    public:
        SpiHw ();

        void      Send16Bits (const uint16_t * v_data, const uint16_t v_len) override;
        uint8_t * Send       (const uint8_t  * v_data, const uint16_t v_len) override;

    private:
        //static spi_device_handle_t spi;
        const  spi_host_device_t   lcdHost = HSPI_HOST;
        const  int                 dmaChan = 2;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
