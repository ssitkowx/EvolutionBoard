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
        enum class ELcd : uint8_t
        {
            eSdi = 19,
            eSdo = 23,
            eSck = 18,
            eCs  = 5,
            eDc  = 22,
            eRst = 21
        };
        enum class ETouch : uint8_t
        {
            eDin = 12,
            eDo  = 13,
            eClk = 14,
            eCs  = 15,
            eIrq = 27
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
