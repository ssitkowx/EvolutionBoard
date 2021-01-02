///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "TouchHw.h"
#include "BitmapHw.h"
#include "KeyboardImages.h"
#include "NumericKeyboard.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

NumericKeyboard::NumericKeyboard (Configuration        v_config,
                                  Display<DisplayHw> & v_display,
                                  Touch<TouchHw>     & v_touch) : config  (v_config),
                                                                  display (v_display),
                                                                  touch   (v_touch)
{
    LOG (MODULE, "Init.");

    // register first row
    uint16_t xPos = config.KeyboardStart.X;
    uint16_t yPos = config.KeyboardStart.Y;

    BitmapHw & keyNum0DownBitmap = create <EId::eKeyNum0Down> (KeyNum0Down, xPos, yPos);
    create <EId::eKeyNum0Up> (KeyNum0Up, xPos, yPos);

    xPos += keyNum0DownBitmap.Dimension.Width + config.BitmapSpacing.X;
    create <EId::eKeyNum1Down> (KeyNum1Down, xPos, yPos);
    create <EId::eKeyNum1Up>   (KeyNum1Up  , xPos, yPos);

    xPos += keyNum0DownBitmap.Dimension.Width + config.BitmapSpacing.X;
    create <EId::eKeyNum2Down> (KeyNum2Down, xPos, yPos);
    create <EId::eKeyNum2Up>   (KeyNum2Up  , xPos, yPos);

    // register second row
    xPos = config.KeyboardStart.X;
    yPos += keyNum0DownBitmap.Dimension.Height + config.BitmapSpacing.Y;
    create <EId::eKeyNum3Down> (KeyNum3Down, xPos, yPos);
    create <EId::eKeyNum3Up>   (KeyNum3Up  , xPos, yPos);

    xPos += keyNum0DownBitmap.Dimension.Width + config.BitmapSpacing.X;
    create <EId::eKeyNum4Down> (KeyNum4Down, xPos, yPos);
    create <EId::eKeyNum4Up>   (KeyNum4Up  , xPos, yPos);

    xPos += keyNum0DownBitmap.Dimension.Width + config.BitmapSpacing.X;
    create <EId::eKeyNum5Down> (KeyNum5Down, xPos, yPos);
    create <EId::eKeyNum5Up>   (KeyNum5Up  , xPos, yPos);

    // register third row
    xPos = config.KeyboardStart.X;
    yPos += keyNum0DownBitmap.Dimension.Height + config.BitmapSpacing.Y;
    create <EId::eKeyNum6Down> (KeyNum6Down, xPos, yPos);
    create <EId::eKeyNum6Up>   (KeyNum6Up  , xPos, yPos);

    xPos += keyNum0DownBitmap.Dimension.Width + config.BitmapSpacing.X;
    create <EId::eKeyNum7Down> (KeyNum7Down, xPos, yPos);
    create <EId::eKeyNum7Up>   (KeyNum7Up  , xPos, yPos);

    xPos += keyNum0DownBitmap.Dimension.Width + config.BitmapSpacing.X;
    create <EId::eKeyNum8Down> (KeyNum8Down, xPos, yPos);
    create <EId::eKeyNum8Up>   (KeyNum8Up  , xPos, yPos);
}

void NumericKeyboard::Process (void)
{
    static Rectangle::Coordinates coordinates;

    Touch<TouchHw>::EState eState = touch.Event ();
    if (eState == Touch<TouchHw>::EState::ePressed)
    {
        coordinates = touch.GetCoordinates ();
        Redraw (static_cast <uint8_t> (EId::eKeyNum0Down), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum1Down), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum2Down), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum3Down), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum4Down), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum5Down), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum6Down), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum7Down), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum8Down), coordinates);
    }

    else if (eState == Touch<TouchHw>::EState::eReleased)
    {
        Redraw (static_cast <uint8_t> (EId::eKeyNum0Up), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum1Up), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum2Up), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum3Up), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum4Up), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum5Up), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum6Up), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum7Up), coordinates);
        Redraw (static_cast <uint8_t> (EId::eKeyNum8Up), coordinates);
    }
    else { }
}

NumericKeyboard::~NumericKeyboard () { unregisterBitmaps (); }

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
