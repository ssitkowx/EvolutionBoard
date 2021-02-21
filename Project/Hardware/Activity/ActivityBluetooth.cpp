///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include "Edit.h"
#include "ActionId.h"
#include "ButtonsImages.h"
#include "BleBackground.h"
#include "ActivityBluetooth.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ActivityBluetooth::ActivityBluetooth (Touch<TouchHw>         & v_touch,
                                      Draftsman<DraftsmanHw> & v_draftsman,
                                      Resources              & v_resources) : touch          (v_touch),
                                                                              resources      (v_resources),
                                                                              background     (v_draftsman),
                                                                              sendButtonDown (v_draftsman),
                                                                              sendButtonUp   (v_draftsman),
                                                                              backButtonDown (v_draftsman),
                                                                              backButtonUp   (v_draftsman),
                                                                              edit           (v_draftsman, v_resources)
{
    LOG (MODULE, "Init.");

    uint16_t xPos = ZERO;
    uint16_t yPos = TWO_HUNDRED_SIXTY;

    background    .Create <static_cast <uint16_t>(EActionId::eBleBackground )> (BleBackground , ZERO  , ZERO);
    edit          .Create <static_cast <uint16_t>(EActionId::eDefault       )> (Edit          , TWENTY, FORTY                              , true);
    sendButtonDown.Create <static_cast <uint16_t>(EActionId::eSendButtonDown)> (SendButtonDown, xPos  , yPos                               , true);
    sendButtonUp  .Create <static_cast <uint16_t>(EActionId::eSendButtonUp  )> (SendButtonUp  , xPos  , yPos                               , true);
    backButtonDown.Create <static_cast <uint16_t>(EActionId::eBackButtonDown)> (BackButtonDown, xPos + sendButtonDown.Dimension.Width, yPos, true);
    backButtonUp  .Create <static_cast <uint16_t>(EActionId::eBackButtonUp  )> (BackButtonUp  , xPos + sendButtonDown.Dimension.Width, yPos, true);

    Subscribe (background);
    Subscribe (edit);
    Subscribe (sendButtonDown);
    Subscribe (sendButtonUp);
    Subscribe (backButtonDown);
    Subscribe (backButtonUp);
}

void ActivityBluetooth::Process (void)
{
    static Bitmap::Coordinates coordinates;

    Touch<TouchHw>::EState eState = touch.Event ();
    if (eState == Touch<TouchHw>::EState::ePressed)
    {
        coordinates = touch.GetCoordinates ();
        sendButtonDown.Draw (static_cast <uint8_t> (EActionId::eSendButtonDown), coordinates);
        backButtonDown.Draw (static_cast <uint8_t> (EActionId::eBackButtonDown), coordinates);
    }
    else if (eState == Touch<TouchHw>::EState::eReleased)
    {
        sendButtonUp.Draw (static_cast <uint8_t> (EActionId::eSendButtonUp), coordinates);
        backButtonUp.Draw (static_cast <uint8_t> (EActionId::eBackButtonUp), coordinates);
    }
    else { }
}

void ActivityBluetooth::Start (void)
{
    Activity::Start ();
    Update ();
}

void ActivityBluetooth::Update (void)
{
    edit.Draw ();
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
