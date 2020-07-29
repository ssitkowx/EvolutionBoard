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

class SpiLcdHw final: public Spi
{
    static constexpr char * MODULE = (char *)"SpiLcdHw";

    public:
        enum class EFlag : uint8_t
        {
            eDio        = ZERO,
            eQio        = ONE,
            eRxData     = TWO,
            eTxData     = THREE,
            eDioQioAddr = FOUR,
            eCmd        = FIVE,
            eAddr       = SIX,
            eDummy      = SEVEN,
            eCd         = SEVEN
        };

        enum class EMode : uint8_t
        {
            eCmd  = ZERO,
            eData = ONE
        };

        SpiLcdHw ();

        void     Send    (const uint8_t *  const v_data, const uint16_t v_len) override;
        void     Send    (const uint16_t * const v_data, const uint16_t v_len) override;
        uint16_t Receive (uint8_t *              v_data)                       override;

    private:
        static spi_device_handle_t spi;
        const  spi_host_device_t   lcdHost = VSPI_HOST;
        const  int                 dmaChan = TWO;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
