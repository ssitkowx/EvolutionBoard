///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "BitmapHw.h"
#include "KeyboardImages.h"
#include "NumericKeyboard.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

NumericKeyboard::NumericKeyboard (Configuration v_config, Display & v_display) : config (v_config), display (v_display)
{
    // register first row
    uint16_t xPos = config.KeyboardStart.X;
    uint16_t yPos = config.KeyboardStart.Y;
    BitmapHw & keyNum0UpBitmap = Create <BitmapHw::EId::eKeyNum0Up> (KeyNum0Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum0Down> (KeyNum0Down, xPos, yPos);

    xPos += keyNum0UpBitmap.Rect.Dimension.Width + config.BitmapSpacing.X;
    BitmapHw & keyNum1UpBitmap = Create <BitmapHw::EId::eKeyNum1Up> (KeyNum1Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum1Down> (KeyNum1Down, xPos, yPos);

    xPos += keyNum1UpBitmap.Rect.Dimension.Width + config.BitmapSpacing.X;
    BitmapHw & keyNum2UpBitmap = Create <BitmapHw::EId::eKeyNum2Up> (KeyNum2Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum2Down> (KeyNum2Down, xPos, yPos);

    // register second row
    xPos = config.KeyboardStart.X;
    yPos += keyNum0UpBitmap.Rect.Dimension.Height + config.BitmapSpacing.Y;
    BitmapHw & keyNum3UpBitmap = Create <BitmapHw::EId::eKeyNum3Up> (KeyNum3Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum3Down> (KeyNum3Down, xPos, yPos);

    xPos += keyNum0UpBitmap.Rect.Dimension.Width + config.BitmapSpacing.X;
    BitmapHw & keyNum4UpBitmap = Create <BitmapHw::EId::eKeyNum4Up> (KeyNum4Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum4Down> (KeyNum4Down, xPos, yPos);

    xPos += keyNum0UpBitmap.Rect.Dimension.Width + config.BitmapSpacing.X;
    BitmapHw & keyNum5UpBitmap = Create <BitmapHw::EId::eKeyNum5Up> (KeyNum5Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum5Down> (KeyNum5Down, xPos, yPos);

    // register third row
    xPos = config.KeyboardStart.X;
    yPos += keyNum0UpBitmap.Rect.Dimension.Height + config.BitmapSpacing.Y;
    BitmapHw & keyNum6UpBitmap = Create <BitmapHw::EId::eKeyNum6Up> (KeyNum6Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum6Down> (KeyNum6Down, xPos, yPos);

    xPos += keyNum0UpBitmap.Rect.Dimension.Width + config.BitmapSpacing.X;
    BitmapHw & keyNum7UpBitmap = Create <BitmapHw::EId::eKeyNum7Up> (KeyNum7Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum7Down> (KeyNum7Down, xPos, yPos);

    xPos += keyNum0UpBitmap.Rect.Dimension.Width + config.BitmapSpacing.X;
    BitmapHw & keyNum8UpBitmap = Create <BitmapHw::EId::eKeyNum8Up> (KeyNum8Up, xPos, yPos);
    Create <BitmapHw::EId::eKeyNum8Down> (KeyNum8Down, xPos, yPos);

    // draw background
    xPos += keyNum0UpBitmap.Rect.Dimension.Width - TWO * config.BitmapSpacing.X;
    yPos += keyNum0UpBitmap.Rect.Dimension.Height - TWO * config.BitmapSpacing.Y;
    Rectangle background = { };
    background.Coordinate.X     = config.KeyboardStart.X - config.BitmapSpacing.X;
    background.Coordinate.Y     = config.KeyboardStart.Y - config.BitmapSpacing.Y;
    background.Dimension.Width  = xPos;
    background.Dimension.Height = yPos;
    display.DrawRect (background, Display::EColors::eNavy);
/*
    // draw first row
    display.DrawBitmap (keyNum0UpBitmap.Rect);
    display.DrawBitmap (keyNum1UpBitmap.Rect);
    display.DrawBitmap (keyNum2UpBitmap.Rect);

    // draw second row
    display.DrawBitmap (keyNum3UpBitmap.Rect);
    display.DrawBitmap (keyNum4UpBitmap.Rect);
    display.DrawBitmap (keyNum5UpBitmap.Rect);

    //draw third row
    display.DrawBitmap (keyNum6UpBitmap.Rect);
    display.DrawBitmap (keyNum7UpBitmap.Rect);
    display.DrawBitmap (keyNum8UpBitmap.Rect);*/
}

NumericKeyboard::~NumericKeyboard () { unregisterBitmaps (); }

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
