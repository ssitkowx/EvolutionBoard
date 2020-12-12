#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include "Display.h"
#include "ILI9341.h"
#include "LoggerHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class DisplayHw final : public Display<DisplayHw>
{
    static constexpr char * MODULE = (char *)"DisplayHw";
    friend Display<DisplayHw>;

    public:
        explicit DisplayHw (const Config_t v_config, ILI9341 & v_ili9341) : Display (v_config),
                                                                            ili9341 (v_ili9341) { LOG (MODULE, "Init."); }
        ~DisplayHw () = default;

        bool    DrawBitmap (Bitmap & v_bitmap);
        bool    DrawText   (std::string & v_text, Rectangle::Coordinates v_coordinate);

    protected:
        void    sendLines  (const Bitmap & v_bitmap);

        // https://www.rapidtables.com/web/color/RGB_Color.html
        // might be unused
        constexpr uint8_t getColor (const EColors v_eColor)
        {
            // R [7:5],
            // B [4:3],
            // G [2:0].

            switch (v_eColor)
            {
                case EColors::eBlack  : { return 0x00; }
                case EColors::eWhite  : { return 0xFF; }
                case EColors::eRed    : { return 0xE0; }
                case EColors::eBlue   : { return 0x18; }
                case EColors::eGreen  : { return 0x07; }
                case EColors::eYellow : { return 0xE7; }
                case EColors::eCyan   : { return 0x1F; }
                case EColors::eMagneta: { return 0xF8; }
                case EColors::eGray   : { return 0x94; }
                case EColors::eMaroon : { return 0x80; }
                case EColors::eOlive  : { return 0x84; }
                case EColors::ePurple : { return 0x90; }
                case EColors::eTeal   : { return 0x14; }
                case EColors::eNavy   : { return 0x10; }
                default               : { return 0xFF; }
            };
        }

    private:
        ILI9341 & ili9341;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
