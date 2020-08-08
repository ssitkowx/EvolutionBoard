#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Gpio.h"
#include <stdint.h>
#include "Display.h"
#include "ILI9341.h"
#include "SpiLcdHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class DisplayHw final : public Display
{
    static constexpr char * MODULE = (char *)"DisplayHw";

    public:
        DisplayHw (Gpio & v_gpio, const Display::Configuration v_config);

        bool     DrawText    (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data, const uint16_t v_len, const Display::EColors eColor     ) override;
        bool     DrawPicture (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data, const uint16_t v_len                                    ) override;

    protected:
        void     sendLines   (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length, const uint16_t * const v_data) override;
        uint8_t  getColor    (const Display::EColors eColor                                                                                               ) override;

    private:
        Gpio &   gpio;
        ILI9341  ili9341;
        SpiLcdHw spiLcdHw;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
