///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "GpioHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void GpioHw::SetPinLevel (const EPinNum v_ePinNum, const bool v_state)
{
    gpio_set_level (static_cast<gpio_num_t>(v_ePinNum), v_state);
}

void GpioHw::SetPinDirection (const EPinNum v_ePinNum, const EPinMode v_ePinMode)
{
    gpio_set_direction (static_cast <gpio_num_t> (v_ePinNum), getPinMode (v_ePinMode));
}

bool GpioHw::ReadPinLevel (const EPinNum v_ePinNum)
{
    return gpio_get_level (static_cast<gpio_num_t>(v_ePinNum));
}

gpio_mode_t GpioHw::getPinMode (const Gpio::EPinMode v_ePinMode)
{
    switch (v_ePinMode)
    {
        case EPinMode::eDisable:
        {
            return GPIO_MODE_DISABLE;
        }
        case EPinMode::eInput:
        {
            return GPIO_MODE_INPUT;
        }
        case EPinMode::eOutput:
        {
            return GPIO_MODE_OUTPUT;
        }
        case EPinMode::eOutputOd:
        {
            return GPIO_MODE_OUTPUT_OD;
        }
        case EPinMode::eInputOutputOd:
        {
            return GPIO_MODE_INPUT_OUTPUT_OD;
        }
        case EPinMode::eInputOutput:
        {
            return GPIO_MODE_INPUT_OUTPUT;
        }
        default:
        {
        }
    }

    // error
    return GPIO_MODE_DISABLE;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
