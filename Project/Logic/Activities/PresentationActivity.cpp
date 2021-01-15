///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Bitmap.h"
#include "Settings.h"
#include "Resources.h"
#include "DraftsmanHw.h"
#include "SystemEvents.h"
#include "PresentationActivity.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

PresentationActivity::PresentationActivity (Draftsman<DraftsmanHw> & v_draftsman,
                                            Button                 & v_button,
                                            Resources              & v_resources) : draftsman (v_draftsman),
                                                                                    button    (v_button),
                                                                                    resources (v_resources)
{
    Bitmap & background = resources [Resources::EId::eBackground];
    draftsman.DrawBitmap (background);

    Bitmap & city            = resources [Resources::EId::eCity];
    uint16_t posX            = startPosX + startMeasureX;
    uint16_t posY            = startPosY;
    uint8_t  movementY       = city.Dimension.Height + FIVE;

    city.Coordinate.X        = startPosX;
    city.Coordinate.Y        = posY;
    draftsman.DrawBitmap (city);
    draftsman.DrawText   (startText, { posX, posY });
    posY += movementY;

    Bitmap & humidity        = resources [Resources::EId::eHumidity];
    humidity.Coordinate.X    = startPosX;
    humidity.Coordinate.Y    = posY;
    draftsman.DrawBitmap (humidity);
    draftsman.DrawText   (startText, { posX, posY });
    posY += movementY;

    Bitmap & pressure        = resources [Resources::EId::ePressure];
    pressure.Coordinate.X    = startPosX;
    pressure.Coordinate.Y    = posY;
    draftsman.DrawBitmap (pressure);
    draftsman.DrawText   (startText, { posX, posY });
    posY += movementY;

    Bitmap & windSpeed       = resources [Resources::EId::eWindSpeed];
    windSpeed.Coordinate.X   = startPosX;
    windSpeed.Coordinate.Y   = posY;
    draftsman.DrawBitmap (windSpeed);
    draftsman.DrawText   (startText, { posX, posY });
    posY += movementY;

    Bitmap & temperature     = resources [Resources::EId::eTemperature];
    temperature.Coordinate.X = startPosX;
    temperature.Coordinate.Y = posY;
    draftsman.DrawBitmap (temperature);
    draftsman.DrawText   (startText, { posX, posY });

    v_button.Redraw ();
}

void PresentationActivity::Process (void)
{
    button.Process ();
    if (SystemEvents::GetInstance ().CircBuf.IsEmpty () == false)
    {
        uint16_t eventId = SystemEvents::GetInstance ().CircBuf.Remove ();
        //LOGI (MODULE, "Event: %d", eventId);
        Update ();
    }
}

void PresentationActivity::Update  (void)
{
    Bitmap & city       = resources [Resources::EId::eCity];
    uint16_t posX       = startPosX + startMeasureX;
    uint16_t posY       = startPosY;
    uint8_t  movementY  = city.Dimension.Height + FIVE;

    draftsman.DrawText (spaces                                                                             , {posX, posY});
    draftsman.DrawText (Settings::GetInstance ().WeatherMeasureMsgType.Location.Country.data ()            , {posX, posY});
    posY += movementY;
    draftsman.DrawText (spaces                                                                             , {posX, posY});
    draftsman.DrawText (std::to_string (Settings::GetInstance ().WeatherMeasureMsgType.Current.Humidity)   , {posX, posY});
    posY += movementY;
    draftsman.DrawText (spaces                                                                             , {posX, posY});
    draftsman.DrawText (std::to_string (Settings::GetInstance ().WeatherMeasureMsgType.Current.Pressure)   , {posX, posY});
    posY += movementY;
    draftsman.DrawText (spaces                                                                             , {posX, posY});
    draftsman.DrawText (std::to_string (Settings::GetInstance ().WeatherMeasureMsgType.Current.WindSpeed)  , {posX, posY});
    posY += movementY;
    draftsman.DrawText (spaces                                                                             , {posX, posY});
    draftsman.DrawText (std::to_string (Settings::GetInstance ().WeatherMeasureMsgType.Current.Temperature), {posX, posY});
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
