#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "TouchHw.h"
#include "BitmapHw.h"
#include "Keyboard.h"
#include "DisplayHw.h"
#include "Rectangle.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class NumericKeyboard final : public Keyboard
{
    public:
        static constexpr char * MODULE = (char *)"NumericKeyboard";

        enum class EId : uint8_t
        {
            eKeyNum0Up,
            eKeyNum0Down,
            eKeyNum1Up,
            eKeyNum1Down,
            eKeyNum2Up,
            eKeyNum2Down,
            eKeyNum3Up,
            eKeyNum3Down,
            eKeyNum4Up,
            eKeyNum4Down,
            eKeyNum5Up,
            eKeyNum5Down,
            eKeyNum6Up,
            eKeyNum6Down,
            eKeyNum7Up,
            eKeyNum7Down,
            eKeyNum8Up,
            eKeyNum8Down,
            eKeyNum9Up,
            eKeyNum9Down
        };

        struct Configuration
        {
            struct BitmapSpacings
            {
                uint8_t X;
                uint8_t Y;
            } BitmapSpacing;

            Rectangle::Coordinates KeyboardStart;
        } config;

        explicit NumericKeyboard (Configuration        v_config,
                                  Display<DisplayHw> & v_display,
                                  Touch<TouchHw>     & v_touch);

        void     Process         (void) override;

        ~NumericKeyboard ();

    private:
        template <const EId ID>
        BitmapHw & create (const uint16_t * v_data, const uint16_t v_xPos = ZERO, const uint16_t v_yPos = ZERO, bool v_isButton = false)
        {
            static BitmapHw bitmap (display);
            bitmap.Id               = static_cast <uint8_t> (ID);
            bitmap.IsButton         = v_isButton;
            bitmap.Coordinate.X     = v_xPos;
            bitmap.Coordinate.Y     = v_yPos;
            bitmap.Dimension.Width  = v_data  [FIRST_BYTE];
            bitmap.Dimension.Height = v_data  [SECOND_BYTE];
            bitmap.Data             = &v_data [THIRD_BYTE];
            registerBitmap (&bitmap);
            return bitmap;
        }

        Display<DisplayHw> & display;
        Touch<TouchHw>     & touch;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
