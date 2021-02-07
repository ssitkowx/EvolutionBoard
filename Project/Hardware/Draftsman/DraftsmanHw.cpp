///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Logger.h"
#include "LoggerHw.h"
#include "Bitmap.h"
#include <optional>
#include "Settings.h"
#include "DraftsmanHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

DraftsmanHw::DraftsmanHw (const Config_t v_config, ILI9341 & v_ili9341, Font & v_font) : Draftsman (v_config),
                                                                                         ili9341   (v_ili9341),
                                                                                         font      (v_font)
{
    LOG (MODULE, "Init.");
}

void DraftsmanHw::DrawText (std::string_view v_text, const Bitmap::Coordinates v_coordinate)
{
    if (v_text.size () == ZERO)
    {
        LOGE (MODULE, "Empty string text.");
        return;
    }

    uint16_t xPos = v_coordinate.X;
    for (uint8_t asciNum = ZERO; asciNum < v_text.size (); asciNum++)
    {
        Bitmap & bitmap     = font [static_cast <Font::EId>(v_text.at (asciNum))];
        bitmap.Coordinate.X = xPos;
        bitmap.Coordinate.Y = v_coordinate.Y;
        xPos               += bitmap.Dimension.Width;
        DrawBitmap (bitmap);
    }
}

bool DraftsmanHw::DrawBitmap (Bitmap & v_bitmap)
{
    if (Draftsman::DrawBitmap (v_bitmap) == false)
    {
        LOGE (MODULE, "Rect out of display: id: %d, xPos: %d, yPos: %d, Width: %d, Height: %d.", v_bitmap.Id,
                                                                                                 v_bitmap.Coordinate.X,
                                                                                                 v_bitmap.Coordinate.Y,
                                                                                                 v_bitmap.Dimension.Width,
                                                                                                 v_bitmap.Dimension.Height);
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
