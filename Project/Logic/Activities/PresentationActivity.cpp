///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include "Font.h"
#include "Bitmap.h"
#include "Settings.h"
#include "DraftsmanHw.h"
#include "SystemEvents.h"
#include "PresentationActivity.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

PresentationActivity::PresentationActivity (Draftsman<DraftsmanHw> & v_draftsman,
                                            Button   <ButtonsHw>   & v_button,
                                            Resources              & v_resources) : draftsman (v_draftsman),
                                                                                    button    (v_button),
                                                                                    resources (v_resources)
{
    LOG (MODULE, "Init.");

    Bitmap & background = resources [Resources::EId::eBackground];
    draftsman.DrawBitmap (background);

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

    v_button.Redraw    ();
}

void PresentationActivity::Process (void)
{
    button.Process ();
    if (SystemEvents::GetInstance ().CircBuf.IsEmpty () == false)
    {
        uint16_t eventId = SystemEvents::GetInstance ().CircBuf.Remove ();
        LOGI (MODULE, "Event: %d", eventId);
        // todo switchig activity ?
    }
}

void PresentationActivity::Update  (void)
{
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
