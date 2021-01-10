///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Bitmap.h"
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

    uint16_t startVariableX  = TEN;
    uint16_t startVariableY  = TEN;
    uint16_t startSpaceX     = ONE_HUNDRED_FIFTY;

    Bitmap & city            = resources [Resources::EId::eCity];
    city.Coordinate.X        = startVariableX;
    city.Coordinate.Y        = startVariableY;
    draftsman.DrawBitmap (city);

    Bitmap & spaces          = resources [Resources::EId::eSpaces];
    spaces.Coordinate.X      = startSpaceX;
    spaces.Coordinate.Y      = startVariableY;
    draftsman.DrawBitmap (spaces);
    draftsman.DrawText   ("?", { spaces.Coordinate.X, spaces.Coordinate.Y });

    Bitmap & humidity        = resources [Resources::EId::eHumidity];
    humidity.Coordinate.X    = startVariableX;
    humidity.Coordinate.Y    = city.Coordinate.Y + humidity.Dimension.Height + FIVE;
    draftsman.DrawBitmap (humidity);

    spaces                   = resources [Resources::EId::eSpaces];
    spaces.Coordinate.X      = startSpaceX;
    spaces.Coordinate.Y      = humidity.Coordinate.Y;
    draftsman.DrawBitmap (spaces);
    draftsman.DrawText   ("?", { spaces.Coordinate.X, spaces.Coordinate.Y });

    Bitmap & pressure        = resources [Resources::EId::ePressure];
    pressure.Coordinate.X    = startVariableX;
    pressure.Coordinate.Y    = humidity.Coordinate.Y + humidity.Dimension.Height + FIVE;
    draftsman.DrawBitmap (pressure);

    spaces                   = resources [Resources::EId::eSpaces];
    spaces.Coordinate.X      = startSpaceX;
    spaces.Coordinate.Y      = pressure.Coordinate.Y;
    draftsman.DrawBitmap (spaces);
    draftsman.DrawText   ("?", { spaces.Coordinate.X, spaces.Coordinate.Y });

    Bitmap & windSpeed       = resources [Resources::EId::eWindSpeed];
    windSpeed.Coordinate.X   = startVariableX;
    windSpeed.Coordinate.Y   = pressure.Coordinate.Y + pressure.Dimension.Height + FIVE;
    draftsman.DrawBitmap (windSpeed);

    spaces                   = resources [Resources::EId::eSpaces];
    spaces.Coordinate.X      = startSpaceX;
    spaces.Coordinate.Y      = windSpeed.Coordinate.Y;
    draftsman.DrawBitmap (spaces);
    draftsman.DrawText   ("?", { spaces.Coordinate.X, spaces.Coordinate.Y });

    Bitmap & temperature     = resources [Resources::EId::eTemperature];
    temperature.Coordinate.X = startVariableX;
    temperature.Coordinate.Y = windSpeed.Coordinate.Y + windSpeed.Dimension.Height + FIVE;
    draftsman.DrawBitmap (temperature);

    spaces                   = resources [Resources::EId::eSpaces];
    spaces.Coordinate.X      = startSpaceX;
    spaces.Coordinate.Y      = temperature.Coordinate.Y;
    draftsman.DrawBitmap (spaces);
    draftsman.DrawText   ("?", { spaces.Coordinate.X, spaces.Coordinate.Y });

    v_button.Redraw ();
}

void PresentationActivity::Process (void)
{
    button.Process ();
    if (SystemEvents::GetInstance ().CircBuf.IsEmpty () == false)
    {
        uint16_t eventId = SystemEvents::GetInstance ().CircBuf.Remove ();
        //LOGI (MODULE, "Event: %d", eventId);
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
