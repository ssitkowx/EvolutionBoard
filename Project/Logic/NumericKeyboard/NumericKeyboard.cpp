///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "BitmapHw.h"
#include "KeyNum1Up.h"
#include "KeyNum1Down.h"
#include "NumericKeyboard.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

NumericKeyboard::NumericKeyboard (Display & v_display) : display (v_display)
{
    static BitmapHw keyNum1Up (v_display);
    keyNum1Up.Rect.Coordinate.X       = FIFTY+100;
    keyNum1Up.Rect.Coordinate.Y       = FIFTY+100;
    keyNum1Up.Rect.Dimension.Width    = KeyNum1Up  [FIRST_BYTE];
    keyNum1Up.Rect.Dimension.Height   = KeyNum1Up  [SECOND_BYTE];
    keyNum1Up.Rect.Data               = &KeyNum1Up [THIRD_BYTE];
    keyNum1Up.Id                      = static_cast <uint8_t> (BitmapHw::EId::eKeyNum1Up);
    registerBitmap (&keyNum1Up);

    static BitmapHw keyNum1Down (v_display);
    keyNum1Down.Rect.Coordinate.X     = FIFTY;
    keyNum1Down.Rect.Coordinate.Y     = FIFTY;
    keyNum1Down.Rect.Dimension.Width  = KeyNum1Down  [FIRST_BYTE];
    keyNum1Down.Rect.Dimension.Height = KeyNum1Down  [SECOND_BYTE];
    keyNum1Down.Rect.Data             = &KeyNum1Down [THIRD_BYTE];
    keyNum1Down.Id                    = static_cast <uint8_t> (BitmapHw::EId::eKeyNum1Down);
    registerBitmap (&keyNum1Down);
}

NumericKeyboard::~NumericKeyboard () { unregisterBitmaps (); }

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
