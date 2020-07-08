#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Spi.h"
#include "Utils.h"
#include "driver/spi_master.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class SpiHw final: public Spi
{
    static constexpr char * MODULE = (char *)"SpiHw";

    public:
        enum class EFlag : uint8_t
        {
            eDio        = 0,
            eQio        = 1,
            eRxData     = 2,
            eTxData     = 3,
            eDioQioAddr = 4,
            eCmd        = 5,
            eAddr       = 6,
            eDummy      = 7,
            eCd         = 7
        };

        enum class EMode : uint8_t
        {
            eCmd  = 0,
            eData = 1
        };

        SpiHw ();

        void      Send16Bits (const uint16_t * v_data, const uint16_t v_len) override;
        uint8_t * Send       (const uint8_t  * v_data, const uint16_t v_len) override;

    private:
        static spi_device_handle_t spi;
        const  spi_host_device_t   lcdHost = HSPI_HOST;
        const  int                 dmaChan = TWO;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
