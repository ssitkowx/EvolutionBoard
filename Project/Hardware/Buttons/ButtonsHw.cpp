///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "Bitmap.h"
#include "TouchHw.h"
#include "ButtonsHw.h"
#include "DraftsmanHw.h"
#include "SystemEvents.h"
#include "ButtonsImages.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ButtonsHw::ButtonsHw (Configuration            v_config,
                      Draftsman<DraftsmanHw> & v_draftsman,
                      Touch<TouchHw>         & v_touch) : config    (v_config),
                                                          draftsman (v_draftsman),
                                                          touch     (v_touch)
{
    LOG (MODULE, "Init.");

    uint16_t xPos = config.Coordinate.X;
    uint16_t yPos = config.Coordinate.Y;

    create <EId::eBleButtonDown> (BleButtonDown, xPos, yPos);
    create <EId::eBleButtonUp>   (BleButtonUp  , xPos, yPos);

    // maybe should be created later after window switch ? todo
    //create <EId::eWeatherButtonDown> (WeatherButtonDown, xPos, yPos);
    //create <EId::eWeatherButtonUp>   (WeatherButtonUp  , xPos, yPos);
}

ButtonsHw::~ButtonsHw () { unregisterBitmaps (); }

void ButtonsHw::Process (void)
{
    static Bitmap::Coordinates coordinates;

    Touch<TouchHw>::EState eState = touch.Event ();
    if (eState == Touch<TouchHw>::EState::ePressed)
    {
        coordinates = touch.GetCoordinates ();
        Redraw (static_cast <uint8_t> (EId::eBleButtonDown), coordinates);
    }
    else if (eState == Touch<TouchHw>::EState::eReleased)
    {
        Redraw (static_cast <uint8_t> (EId::eBleButtonUp), coordinates);
    }
    else { }
}

void ButtonsHw::Redraw (void)
{
    for (auto & bitmap : Bitmaps) { draftsman.DrawBitmap (*bitmap); }
}

void ButtonsHw::Redraw (const uint8_t v_id, const Bitmap::Coordinates & v_coordinates)
{
    for (auto & bitmap : Bitmaps)
    {
        if (Button::Redraw (*bitmap, v_id, v_coordinates) == true)
        {
            if (bitmap->IsButton == true) { SystemEvents::GetInstance ().CircBuf.Add (v_id); }
            draftsman.DrawBitmap (*bitmap);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
