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
        void        SetPinLevel     (const EPinNum v_ePinNum, const bool v_state)        override;
        void        SetPinDirection (const EPinNum v_ePinNum, const EPinMode v_ePinMode) override;
        bool        ReadPinLevel    (const EPinNum v_ePinNum)                            override;

    private:
        gpio_mode_t getPinMode      (const EPinMode v_ePinMode);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
