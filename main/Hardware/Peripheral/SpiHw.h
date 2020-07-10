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

        SpiHw ();

        void     Send    (const uint8_t *  const v_data, const uint16_t v_len) override;
        void     Send    (const uint16_t * const v_data, const uint16_t v_len) override;
        uint16_t Receive (uint8_t *              v_data, const uint16_t v_len) override;

    private:
        static spi_device_handle_t spi;
        const  spi_host_device_t   lcdHost = HSPI_HOST;
        const  int                 dmaChan = TWO;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
