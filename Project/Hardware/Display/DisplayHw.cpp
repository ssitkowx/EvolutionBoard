///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Settings.h"
#include "DisplayHw.h"
#include "Rectangle.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

bool DisplayHw::DrawBitmap (Bitmap & v_bitmap)
{
    if (Display<DisplayHw>::DrawBitmap (v_bitmap) == false)
    {
        LOGE (MODULE, "Rect out of display: xPos: %d, yPos: %d, Width: %d, Height: %d", v_bitmap.Coordinate.X, v_bitmap.Coordinate.Y, v_bitmap.Dimension.Width, v_bitmap.Dimension.Height);
        return false;
    }

    return true;
}

void DisplayHw::sendLines (const Bitmap & v_bitmap)
{
    ili9341.SendLines (v_bitmap);
}

// https://www.rapidtables.com/web/color/RGB_Color.html
uint8_t DisplayHw::getColor (const EColors v_eColor)
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

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
