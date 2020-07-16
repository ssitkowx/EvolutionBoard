#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Gpio.h"
#include <stdint.h>
#include "driver/gpio.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class GpioHw final: public Gpio
{
    static constexpr char * MODULE = (char *)"RtosHw";

    public:

        enum class EPinNum : uint8_t
        {
            eMiso = 25,
            eMosi = 23,
            eClk  = 19,
            eCs   = 22,
            eDc   = 21,
            eRst  = 18,
            eBclk = 5
        };

        enum class EPinMode
        {
            eDisable,
            eInput,
            eOutput,
            eOutputOd,
            eInputOutputOd,
            eInputOutput
        };

        void        SetPinLevel     (const uint16_t v_num, const bool v_state)    override;
        void        SetPinDirection (const uint16_t v_num, const uint16_t v_mode) override;
        bool        ReadPinLevel    (const uint16_t v_num)                        override;

    private:
        gpio_mode_t getPinMode      (const EPinMode v_eMode);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
