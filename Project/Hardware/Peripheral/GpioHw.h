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
    static constexpr char * MODULE = (char *)"GpioHw";

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

        enum class EPinMode : uint32_t
        {
            eDisable,
            eInput  = GPIO_MODE_INPUT,
            eOutput = GPIO_MODE_OUTPUT,
            eOutputOd,
            eInputOutputOd,
            eInputOutput
        };

        enum class EInterrupt : uint8_t
        {
            eDisable          = GPIO_INTR_DISABLE,
            eRising           = GPIO_INTR_POSEDGE,
            eFalling          = GPIO_INTR_NEGEDGE,
            eRisingAndFalling = GPIO_INTR_ANYEDGE,
            eLow              = GPIO_INTR_LOW_LEVEL,
            eHigh             = GPIO_INTR_HIGH_LEVEL
        };

        GpioHw  ();
        ~GpioHw ();

        void        SetPinLevel     (const uint16_t v_num, const bool v_state)    override;
        void        SetPinDirection (const uint16_t v_num, const uint16_t v_mode) override;
        bool        ReadPinLevel    (const uint16_t v_num)                        override;

    private:
        gpio_mode_t getPinMode      (const EPinMode v_eMode);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
