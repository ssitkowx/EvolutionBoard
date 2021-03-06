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

class GpioHw final: public Gpio<GpioHw>
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
            eDisable       = GPIO_MODE_DISABLE,
            eInput         = GPIO_MODE_INPUT,
            eOutput        = GPIO_MODE_OUTPUT,
            eOutputOd      = GPIO_MODE_OUTPUT_OD,
            eInputOutputOd = GPIO_MODE_INPUT_OUTPUT_OD,
            eInputOutput   = GPIO_MODE_INPUT_OUTPUT
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

        GpioHw ();
       ~GpioHw ();

        void        SetPinLevel     (const uint16_t v_num, const bool v_state);
        void        SetPinDirection (const uint16_t v_num, const uint16_t v_mode);
        bool        ReadPinLevel    (const uint16_t v_num);

    private:
        constexpr gpio_mode_t getPinMode (const EPinMode v_eMode)
        {
            switch (v_eMode)
            {
                case EPinMode::eDisable:       { return GPIO_MODE_DISABLE;         }
                case EPinMode::eInput:         { return GPIO_MODE_INPUT;           }
                case EPinMode::eOutput:        { return GPIO_MODE_OUTPUT;          }
                case EPinMode::eOutputOd:      { return GPIO_MODE_OUTPUT_OD;       }
                case EPinMode::eInputOutputOd: { return GPIO_MODE_INPUT_OUTPUT_OD; }
                case EPinMode::eInputOutput:   { return GPIO_MODE_INPUT_OUTPUT;    }
                default:                       { }
            }

            return GPIO_MODE_DISABLE;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
