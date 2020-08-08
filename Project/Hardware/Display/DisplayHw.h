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
        DisplayHw (Gpio & v_gpio);

        void     DrawRect       (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length, const Display::EColors eColor) override;
        void     DrawText       (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data  , const uint16_t v_len   , const Display::EColors eColor) override;
        void     DrawPicture    (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data  , const uint16_t v_len)                                   override;

    private:
        Gpio &   gpio;
        ILI9341  ili9341;
        SpiLcdHw spiLcdHw;

        void     sendLines      (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length, const uint16_t * const v_data);
        bool     validateRect   (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length);
        uint8_t  getColor       (const Display::EColors eColor);
        uint8_t  calculateRects (const uint16_t v_length);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
