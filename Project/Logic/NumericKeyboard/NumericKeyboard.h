#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "BitmapHw.h"
#include "Keyboard.h"
#include "Rectangle.h"
#include "DisplayHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class NumericKeyboard : public Keyboard
{
    public:
        static constexpr char * MODULE = (char *)"NumericKeyboard";

        struct Configuration
        {
            struct BitmapSpacings
            {
                uint8_t X;
                uint8_t Y;
            } BitmapSpacing;

            Rectangle::Coordinates KeyboardStart;
        } config;

        explicit NumericKeyboard (Configuration v_config, Display & v_display);

        template <const BitmapHw::EId ID>
        BitmapHw & Create (const uint16_t * v_data, const uint16_t v_xPos, const uint16_t v_yPos)
        {
            static BitmapHw bitmap (static_cast <uint8_t> (ID), display);
            bitmap.Rect.Coordinate.X     = v_xPos;
            bitmap.Rect.Coordinate.Y     = v_yPos;
            bitmap.Rect.Dimension.Width  = v_data  [FIRST_BYTE];
            bitmap.Rect.Dimension.Height = v_data  [SECOND_BYTE];
            bitmap.Rect.Data             = &v_data [THIRD_BYTE];
            registerBitmap (&bitmap);
            return bitmap;
        }

        ~NumericKeyboard ();

    private:
        Display & display;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
