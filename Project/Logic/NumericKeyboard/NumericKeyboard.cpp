///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "BitmapHw.h"
#include "TouchHw.h"
#include "KeyboardImages.h"
#include "NumericKeyboard.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

NumericKeyboard::NumericKeyboard (Configuration v_config, Display<DisplayHw> & v_display, Touch<TouchHw> & v_touch) : config  (v_config),
                                                                                                                      display (v_display),
                                                                                                                      touch   (v_touch)
{
    LOG (MODULE, "Init.");

    // register first row
    uint16_t xPos = config.KeyboardStart.X;
    uint16_t yPos = config.KeyboardStart.Y;
    BitmapHw & keyNum0UpBitmap = Create <BitmapHw::EId::eKeyNum0Up> (KeyNum0Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum0Down> (KeyNum0Down, xPos, yPos);

    xPos += keyNum0UpBitmap.Dimension.Width + config.BitmapSpacing.X;
    BitmapHw & keyNum1UpBitmap = Create <BitmapHw::EId::eKeyNum1Up> (KeyNum1Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum1Down> (KeyNum1Down, xPos, yPos);

    xPos += keyNum1UpBitmap.Dimension.Width + config.BitmapSpacing.X;
    BitmapHw & keyNum2UpBitmap = Create <BitmapHw::EId::eKeyNum2Up> (KeyNum2Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum2Down> (KeyNum2Down, xPos, yPos);

    // register second row
    xPos = config.KeyboardStart.X;
    yPos += keyNum0UpBitmap.Dimension.Height + config.BitmapSpacing.Y;
    BitmapHw & keyNum3UpBitmap = Create <BitmapHw::EId::eKeyNum3Up> (KeyNum3Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum3Down> (KeyNum3Down, xPos, yPos);

    xPos += keyNum0UpBitmap.Dimension.Width + config.BitmapSpacing.X;
    BitmapHw & keyNum4UpBitmap = Create <BitmapHw::EId::eKeyNum4Up> (KeyNum4Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum4Down> (KeyNum4Down, xPos, yPos);

    xPos += keyNum0UpBitmap.Dimension.Width + config.BitmapSpacing.X;
    BitmapHw & keyNum5UpBitmap = Create <BitmapHw::EId::eKeyNum5Up> (KeyNum5Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum5Down> (KeyNum5Down, xPos, yPos);

    // register third row
    xPos = config.KeyboardStart.X;
    yPos += keyNum0UpBitmap.Dimension.Height + config.BitmapSpacing.Y;
    BitmapHw & keyNum6UpBitmap = Create <BitmapHw::EId::eKeyNum6Up> (KeyNum6Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum6Down> (KeyNum6Down, xPos, yPos);

    xPos += keyNum0UpBitmap.Dimension.Width + config.BitmapSpacing.X;
    BitmapHw & keyNum7UpBitmap = Create <BitmapHw::EId::eKeyNum7Up> (KeyNum7Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum7Down> (KeyNum7Down, xPos, yPos);

    xPos += keyNum0UpBitmap.Dimension.Width + config.BitmapSpacing.X;
    BitmapHw & keyNum8UpBitmap = Create <BitmapHw::EId::eKeyNum8Up> (KeyNum8Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum8Down> (KeyNum8Down, xPos, yPos);
/*
    // draw background
    xPos -= FOUR * config.BitmapSpacing.X;
    yPos += FOUR * config.BitmapSpacing.Y;
    Rectangle background = { };
    background.Coordinate.X     = config.KeyboardStart.X - config.BitmapSpacing.X;
    background.Coordinate.Y     = config.KeyboardStart.Y - config.BitmapSpacing.Y;
    background.Dimension.Width  = xPos;
    background.Dimension.Height = yPos;
    display.Draw (background, Display::EColors::eNavy);
*/
    // draw first row
    display.DrawBitmap (keyNum0UpBitmap);
    display.DrawBitmap (keyNum1UpBitmap);
    display.DrawBitmap (keyNum2UpBitmap);

    // draw second row
    display.DrawBitmap (keyNum3UpBitmap);
    display.DrawBitmap (keyNum4UpBitmap);
    display.DrawBitmap (keyNum5UpBitmap);

    //draw third row
    display.DrawBitmap (keyNum6UpBitmap);
    display.DrawBitmap (keyNum7UpBitmap);
    display.DrawBitmap (keyNum8UpBitmap);
}

void NumericKeyboard::Process (void)
{
    // need hardware fix this is working too often
    Touch<TouchHw>::EState eState = touch.Event ();    // since now its not logic anymore. Move to hardware todo
    static Rectangle::Coordinates coordinates;
    if (eState == Touch<TouchHw>::EState::ePressed)
    {
        coordinates = touch.GetCoordinates ();
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum0Down), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum1Down), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum2Down), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum3Down), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum4Down), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum5Down), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum6Down), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum7Down), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum8Down), coordinates);
    }

    else if (eState == Touch<TouchHw>::EState::eReleased)
    {
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum0Up), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum1Up), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum2Up), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum3Up), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum4Up), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum5Up), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum6Up), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum7Up), coordinates);
        Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum8Up), coordinates);
    }
    else
    {

    }
}

NumericKeyboard::~NumericKeyboard () { unregisterBitmaps (); }

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
