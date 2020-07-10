///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "GpioHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void GpioHw::SetPinLevel (const uint16_t v_num, const bool v_state)
{
    gpio_set_level (static_cast<gpio_num_t>(v_num), v_state);
}

void GpioHw::SetPinDirection (const uint16_t v_num, const uint16_t v_mode)
{
    gpio_set_direction (static_cast <gpio_num_t> (v_num), getPinMode (static_cast <EPinMode> (v_mode)));
}

bool GpioHw::ReadPinLevel (const uint16_t v_num)
{
    return gpio_get_level (static_cast<gpio_num_t>(v_num));
}

gpio_mode_t GpioHw::getPinMode (const EPinMode v_eMode)
{
    switch (v_eMode)
    {
        case EPinMode::eDisable:       { return GPIO_MODE_DISABLE;         }
        case EPinMode::eInput:         { return GPIO_MODE_INPUT;           }
        case EPinMode::eOutput:        { return GPIO_MODE_OUTPUT;          }
        case EPinMode::eOutputOd:      { return GPIO_MODE_OUTPUT_OD;       }
        case EPinMode::eInputOutputOd: { return GPIO_MODE_INPUT_OUTPUT_OD; }
        case EPinMode::eInputOutput:   { return GPIO_MODE_INPUT_OUTPUT;    }
        default: { }
    }

    // error
    return GPIO_MODE_DISABLE;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
