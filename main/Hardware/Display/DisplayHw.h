#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Spi.h"
#include "Gpio.h"
#include <stdint.h>
#include "Display.h"
#include "ILI9341.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class DisplayHw final : public Display
{
    static constexpr char * MODULE = (char *)"DisplayHw";

    public:
        DisplayHw (Gpio & v_gpio, Spi & v_spi);

        void     DrawRect       (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length, const uint32_t v_color) override;
        void     DrawText       (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data  , const uint16_t v_len)                            override;
        void     DrawPicture    (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data  , const uint16_t v_len)                            override;

    private:
        Gpio &  gpio;
        Spi  &  spi;
        ILI9341 ili9341;

        void     sendLines      (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length, const uint16_t * const v_data);
        bool     validateRect   (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length);
        uint8_t  calculateRects (const uint16_t v_length);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
