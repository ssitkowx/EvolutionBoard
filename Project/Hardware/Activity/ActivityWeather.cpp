///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Settings.h"
#include "BitmapId.h"
#include "Resources.h"
#include "ButtonsImages.h"
#include "ActivityWeather.h"
#include "WeatherBackground.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ActivityWeather::ActivityWeather (Touch<TouchHw>         & v_touch,
                                  Draftsman<DraftsmanHw> & v_draftsman,
                                  Resources              & v_resources) : touch      (v_touch),
                                                                          draftsman  (v_draftsman),
                                                                          resources  (v_resources),
                                                                          background (v_draftsman),
                                                                          buttonDown (v_draftsman),
                                                                          buttonUp   (v_draftsman)

{
    LOG (MODULE, "Init.");

    uint16_t xPos = FIFTEEN;
    uint16_t yPos = TWO_HUNDRED_SIXTY;

    background.Create <static_cast <uint16_t>(EBitmapId::eWeatherBackground)> (WeatherBackground, ZERO, ZERO);
    buttonDown.Create <static_cast <uint16_t>(EBitmapId::eWeatherButtonDown)> (WeatherButtonDown, xPos, yPos, true);
    buttonUp  .Create <static_cast <uint16_t>(EBitmapId::eWeatherButtonUp)  > (WeatherButtonUp  , xPos, yPos, true);

    Subscribe (background);
    Subscribe (buttonDown);
    Subscribe (buttonUp);
}

void ActivityWeather::Start (void)
{
    Activity::Start ();

    Bitmap & letter    = resources [Font::EId::eA];
    uint16_t posX      = startPosX + startMeasureX;
    uint16_t posY      = startPosY;
    uint8_t  movementY = letter.Dimension.Height + FIVE;

    draftsman.DrawText ("City:"       , { startPosX, posY });
    draftsman.DrawText (startText     , { posX     , posY });
    posY += movementY;

    draftsman.DrawText ("Humidity:"   , { startPosX, posY });
    draftsman.DrawText (startText     , { posX     , posY });
    posY += movementY;

    draftsman.DrawText ("Pressure:"   , { startPosX, posY });
    draftsman.DrawText (startText     , { posX     , posY });
    posY += movementY;

    draftsman.DrawText ("Wind speed:" , { startPosX, posY });
    draftsman.DrawText (startText     , { posX     , posY });
    posY += movementY;

    draftsman.DrawText ("Temperature:", { startPosX, posY });
    draftsman.DrawText (startText     , { posX, posY });
}

void ActivityWeather::Process (void)
{
    static Bitmap::Coordinates coordinates;

    Touch<TouchHw>::EState eState = touch.Event ();
    if (eState == Touch<TouchHw>::EState::ePressed)
    {
        coordinates = touch.GetCoordinates ();
        buttonDown.Draw (static_cast <uint8_t> (EBitmapId::eWeatherButtonDown), coordinates);
    }
    else if (eState == Touch<TouchHw>::EState::eReleased)
    {
        buttonUp.Draw (static_cast <uint8_t> (EBitmapId::eWeatherButtonUp), coordinates);
        Rtos::GetInstance ()->SetBitsEventGroup ("SwitchToBluetoothActivity");
    }
    else { }
}

void ActivityWeather::Update (void)
{
    Activity::Update ();

    Bitmap & letter    = resources [Font::EId::eA];
    uint16_t posX      = startPosX + startMeasureX;
    uint16_t posY      = startPosY;
    uint8_t  movementY = letter.Dimension.Height + FIVE;

    draftsman.DrawText (spaces                                                                              , {posX, posY});
    draftsman.DrawText (Settings::GetInstance                 ().WeatherMeasureMsgType.Location.Name.data (), {posX, posY});
    posY += movementY;
    draftsman.DrawText (spaces                                                                              , {posX, posY});
    draftsman.DrawText (std::to_string (Settings::GetInstance ().WeatherMeasureMsgType.Current.Humidity)    , {posX, posY});
    posY += movementY;
    draftsman.DrawText (spaces                                                                              , {posX, posY});
    draftsman.DrawText (std::to_string (Settings::GetInstance ().WeatherMeasureMsgType.Current.Pressure)    , {posX, posY});
    posY += movementY;
    draftsman.DrawText (spaces                                                                              , {posX, posY});
    draftsman.DrawText (std::to_string (Settings::GetInstance ().WeatherMeasureMsgType.Current.WindSpeed)   , {posX, posY});
    posY += movementY;
    draftsman.DrawText (spaces                                                                              , {posX, posY});
    draftsman.DrawText (std::to_string (Settings::GetInstance ().WeatherMeasureMsgType.Current.Temperature) , {posX, posY});
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
