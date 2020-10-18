///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "BitmapHw.h"
#include "BaseWindow.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void BaseWindow::Process (void)
{
    bool state = touch.IsPressed ();
    Rectangle rect = { };

    //simulation because touch issue
    rect.Coordinate.X = 150;
    rect.Coordinate.Y = 100;
    state = true;
    //end

    if (state == true)
    {
        //LOGD (MODULE, "pressed");
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum0Down), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum1Down), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum2Down), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum3Down), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum4Down), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum5Down), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum6Down), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum7Down), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum8Down), rect);
    }
    else
    {
        //LOGD (MODULE, "pressed not");
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum0Up), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum1Up), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum2Up), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum3Up), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum4Up), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum5Up), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum6Up), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum7Up), rect);
        keyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum8Up), rect);
    }
}


///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
