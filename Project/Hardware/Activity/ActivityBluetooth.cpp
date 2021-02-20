///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
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
                                                                              edit           (v_draftsman)
{
    LOG (MODULE, "Init.");

    uint16_t xPos = SIXTY;
    uint16_t yPos = TWO_HUNDRED_SIXTY;

    background    .Create <static_cast <uint16_t>(EActionId::eBleBackground )> (BleBackground, ZERO, ZERO);
    sendButtonDown.Create <static_cast <uint16_t>(EActionId::eSendButtonDown)> (SendButtonDown, xPos, yPos - 100, true);
    sendButtonUp  .Create <static_cast <uint16_t>(EActionId::eSendButtonUp  )> (SendButtonUp  , xPos, yPos - 100, true);
    backButtonDown.Create <static_cast <uint16_t>(EActionId::eBackButtonDown)> (BackButtonDown, xPos, yPos, true);
    backButtonUp  .Create <static_cast <uint16_t>(EActionId::eBackButtonUp  )> (BackButtonUp  , xPos, yPos, true);

    Subscribe (background);
    Subscribe (sendButtonDown);
    Subscribe (sendButtonUp);
    Subscribe (backButtonDown);
    Subscribe (backButtonUp);
    Subscribe (edit);
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

}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
