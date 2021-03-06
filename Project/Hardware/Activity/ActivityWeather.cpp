///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Settings.h"
#include "ActionId.h"
#include "Resources.h"
#include "ButtonsImages.h"
#include "ActivityWeather.h"
#include "WeatherBackground.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ActivityWeather::ActivityWeather (Touch<TouchHw>         & v_touch,
                                  Draftsman<DraftsmanHw> & v_draftsman,
                                  Resources              & v_resources) : touch           (v_touch),
                                                                          draftsman       (v_draftsman),
                                                                          resources       (v_resources),
                                                                          background      (v_draftsman),
                                                                          bleButtonUp     (v_draftsman),
                                                                          bleButtonDown   (v_draftsman)

{
    uint16_t xPos = SIXTY;
    uint16_t yPos = TWO_HUNDRED_SIXTY;

    background   .Create <static_cast <uint16_t>(EActionId::eDefault      )> (WeatherBackground, ZERO, ZERO);
    bleButtonDown.Create <static_cast <uint16_t>(EActionId::eBleButtonDown)> (BleButtonDown    , xPos, yPos, true);
    bleButtonUp  .Create <static_cast <uint16_t>(EActionId::eBleButtonUp  )> (BleButtonUp      , xPos, yPos, true);

    Subscribe (background);
    Subscribe (bleButtonDown);
    Subscribe (bleButtonUp);
}

void ActivityWeather::Process (void)
{
    static Bitmap::Coordinates coordinates;

    Touch<TouchHw>::EState eState = touch.Event ();
    if (eState == Touch<TouchHw>::EState::ePressed)
    {
        coordinates = touch.GetCoordinates ();
        bleButtonDown.Draw (static_cast <uint16_t>(EActionId::eBleButtonDown), coordinates);
    }
    else if (eState == Touch<TouchHw>::EState::eReleased)
    {
        bleButtonUp.Draw (static_cast <uint16_t>(EActionId::eBleButtonUp), coordinates);
    }
    else { }
}

void ActivityWeather::Start (const uint16_t v_actionId)
{
    Activity::Start ();
    Update          (v_actionId);
}

void ActivityWeather::Update (const uint16_t v_actionId)
{
    const uint16_t xLeftPos   = TEN;
    const uint8_t  xMiddlePos = xLeftPos   + EIGHTY;
    const uint16_t xRightPos  = xMiddlePos + EIGHTY;
    uint16_t       yPos       = ONE_HUNDRED_FIFTEEN;

    // City
    draftsman.DrawText (Spaces                                                                             , { xLeftPos  , yPos });
    draftsman.DrawText (Settings::GetInstance ().WeatherMeasureMsgType.Location.Name.data ()               , { xLeftPos  , yPos });

    // Humidity
    draftsman.DrawText (Spaces                                                                             , { xMiddlePos, yPos });
    draftsman.DrawText (std::to_string (Settings::GetInstance ().WeatherMeasureMsgType.Current.Humidity)   , { xMiddlePos, yPos });

    // Cloud cover
    draftsman.DrawText (Spaces                                                                             , { xRightPos , yPos });
    draftsman.DrawText (std::to_string (Settings::GetInstance ().WeatherMeasureMsgType.Current.CloudCover) , { xRightPos , yPos });

    yPos += ONE_HUNDRED_TEN;

    // Wind Speed
    draftsman.DrawText (Spaces                                                                             , { xLeftPos  , yPos });
    draftsman.DrawText (std::to_string (Settings::GetInstance ().WeatherMeasureMsgType.Current.WindSpeed)  , { xLeftPos  , yPos });

    // Temperature
    draftsman.DrawText (Spaces                                                                             , { xMiddlePos, yPos });
    draftsman.DrawText (std::to_string (Settings::GetInstance ().WeatherMeasureMsgType.Current.Temperature), { xMiddlePos, yPos });

    // Pressure
    draftsman.DrawText (Spaces                                                                             , { xRightPos , yPos });
    draftsman.DrawText (std::to_string (Settings::GetInstance ().WeatherMeasureMsgType.Current.Pressure)   , { xRightPos , yPos });

    Activity::Update ();
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
