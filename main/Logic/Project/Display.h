#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Spi.h"
#include "Gpio.h"
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Settings
{
    public:
        struct Lcd
        {
            uint8_t  RectsNumber;
            uint16_t Length;
            uint16_t Width;
            uint16_t MaxLinesPerTransfer;
        } Lcd;

        Settings ()
        {
            Lcd.Length              = 320;
            Lcd.Width               = 240;
            Lcd.MaxLinesPerTransfer = 16;     // Limits transfer and heap use
            Lcd.RectsNumber         = 15;     // Divides image into rects = .Width / .MaxLinesInOneTransfer.
        }

        static Settings & GetInstance (void)
        {
            static Settings instance;
            return instance;
        }
};

class Display
{
    public:
        Display (Gpio & v_gpio, Spi & v_spi);

        void    Init           (void);
        void    DrawRect       (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_length, const uint16_t v_width, const uint16_t v_color);

    private:
        Gpio & gpio;
        Spi  & spi;

        void     sendLines      (const uint16_t v_xPos   , const uint16_t v_yPos, const uint16_t v_length, const uint16_t v_width, const uint16_t * v_data);
        uint8_t  calculateRects (const uint16_t v_length , const uint16_t v_width);
        bool     validateRect   (const uint16_t v_xPos   , const uint16_t v_yPos, const uint16_t v_length, const uint16_t v_width);
        uint32_t getId          (void);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
