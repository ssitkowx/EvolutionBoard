#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "BitmapHw.h"
#include "Keyboard.h"
#include "DisplayHw.h"
#include "Rectangle.h"

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
            static BitmapHw bitmap (display);
            bitmap.Id               = static_cast <uint8_t> (ID);
            bitmap.Coordinate.X     = v_xPos;
            bitmap.Coordinate.Y     = v_yPos;
            bitmap.Dimension.Width  = v_data  [FIRST_BYTE];
            bitmap.Dimension.Height = v_data  [SECOND_BYTE];
            bitmap.Data             = &v_data [THIRD_BYTE];
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
