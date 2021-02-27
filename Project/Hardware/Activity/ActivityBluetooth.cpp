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
                                      Resources              & v_resources) : touch       (v_touch),
                                                                              resources   (v_resources),
                                                                              background  (v_draftsman),
                                                                              aButtonDown (v_draftsman),
                                                                              aButtonUp   (v_draftsman),
                                                                              bButtonDown (v_draftsman),
                                                                              bButtonUp   (v_draftsman),
                                                                              sButtonDown (v_draftsman),
                                                                              sButtonUp   (v_draftsman),
                                                                              rButtonDown (v_draftsman),
                                                                              rButtonUp   (v_draftsman),
                                                                              xButtonDown (v_draftsman),
                                                                              xButtonUp   (v_draftsman),
                                                                              zButtonDown (v_draftsman),
                                                                              zButtonUp   (v_draftsman),
                                                                              edit        (v_draftsman, v_resources)
{
    LOG (MODULE, "Init.");

    uint16_t xPos = FORTY_FIVE;
    uint16_t yPos = TWO_HUNDRED;

    background .Create <static_cast <uint16_t>(EActionId::eBleBackground)> (BleBackground, ZERO              , ZERO);
    edit       .Create <static_cast <uint16_t>(EActionId::eDefault      )> (Edit         , TWENTY            , FORTY       , true);

    // first row
    aButtonDown.Create <static_cast <uint16_t>(EActionId::eAButtonDown  )> (AButtonDown  , xPos              , yPos        , true);
    aButtonUp  .Create <static_cast <uint16_t>(EActionId::eAButtonUp    )> (AButtonUp    , xPos              , yPos        , true);
    zButtonDown.Create <static_cast <uint16_t>(EActionId::eZButtonDown  )> (ZButtonDown  , xPos + FIFTY      , yPos        , true);
    zButtonUp  .Create <static_cast <uint16_t>(EActionId::eZButtonUp    )> (ZButtonUp    , xPos + FIFTY      , yPos        , true);
    xButtonDown.Create <static_cast <uint16_t>(EActionId::eXButtonDown  )> (XButtonDown  , xPos + ONE_HUNDRED, yPos        , true);
    xButtonUp  .Create <static_cast <uint16_t>(EActionId::eXButtonUp    )> (XButtonUp    , xPos + ONE_HUNDRED, yPos        , true);

    // second row
    sButtonDown.Create <static_cast <uint16_t>(EActionId::eSButtonDown  )> (SButtonDown  , xPos              , yPos + FIFTY, true);
    sButtonUp  .Create <static_cast <uint16_t>(EActionId::eSButtonUp    )> (SButtonUp    , xPos              , yPos + FIFTY, true);
    rButtonDown.Create <static_cast <uint16_t>(EActionId::eRButtonDown  )> (RButtonDown  , xPos + FIFTY      , yPos + FIFTY, true);
    rButtonUp  .Create <static_cast <uint16_t>(EActionId::eRButtonUp    )> (RButtonUp    , xPos + FIFTY      , yPos + FIFTY, true);
    bButtonDown.Create <static_cast <uint16_t>(EActionId::eBButtonDown  )> (BButtonDown  , xPos + ONE_HUNDRED, yPos + FIFTY, true);
    bButtonUp  .Create <static_cast <uint16_t>(EActionId::eBButtonUp    )> (BButtonUp    , xPos + ONE_HUNDRED, yPos + FIFTY, true);

    Subscribe (background);
    Subscribe (edit);
    Subscribe (aButtonDown);
    Subscribe (aButtonUp);
    Subscribe (bButtonDown);
    Subscribe (bButtonUp);
    Subscribe (sButtonDown);
    Subscribe (sButtonUp);
    Subscribe (rButtonDown);
    Subscribe (rButtonUp);
    Subscribe (xButtonDown);
    Subscribe (xButtonUp);
    Subscribe (zButtonDown);
    Subscribe (zButtonUp);
}

void ActivityBluetooth::Process (void)
{
    static Bitmap::Coordinates coordinates;

    Touch<TouchHw>::EState eState = touch.Event ();
    if (eState == Touch<TouchHw>::EState::ePressed)
    {
        coordinates = touch.GetCoordinates ();
        aButtonDown.Draw (static_cast <uint16_t> (EActionId::eAButtonDown), coordinates);
        bButtonDown.Draw (static_cast <uint16_t> (EActionId::eBButtonDown), coordinates);
        sButtonDown.Draw (static_cast <uint16_t> (EActionId::eSButtonDown), coordinates);
        rButtonDown.Draw (static_cast <uint16_t> (EActionId::eRButtonDown), coordinates);
        xButtonDown.Draw (static_cast <uint16_t> (EActionId::eXButtonDown), coordinates);
        zButtonDown.Draw (static_cast <uint16_t> (EActionId::eZButtonDown), coordinates);
    }
    else if (eState == Touch<TouchHw>::EState::eReleased)
    {
        aButtonUp.Draw (static_cast <uint16_t> (EActionId::eAButtonUp), coordinates);
        bButtonUp.Draw (static_cast <uint16_t> (EActionId::eBButtonUp), coordinates);
        sButtonUp.Draw (static_cast <uint16_t> (EActionId::eSButtonUp), coordinates);
        rButtonUp.Draw (static_cast <uint16_t> (EActionId::eRButtonUp), coordinates);
        xButtonUp.Draw (static_cast <uint16_t> (EActionId::eXButtonUp), coordinates);
        zButtonUp.Draw (static_cast <uint16_t> (EActionId::eZButtonUp), coordinates);
    }
    else { }
}

void ActivityBluetooth::Start (const uint16_t v_actionId)
{
    Activity::Start ();
    Update          (v_actionId);
}

void ActivityBluetooth::Update (const uint16_t v_actionId)
{
    switch (v_actionId)
    {
        case static_cast<uint16_t>(EActionId::eAButtonDown):
        {
            edit.Text.erase();
            edit.Text.append ("Send weather measurement.");
            break;
        }
        case static_cast<uint16_t>(EActionId::eXButtonDown):
        {
            edit.Text.erase();
            edit.Text.append ("Connect with another bluetooth.");
            break;
        }
        case static_cast<uint16_t>(EActionId::eZButtonDown):
        {
            edit.Text.erase();
            edit.Text.append ("Stairway to heaven.");
            break;
        }
        default: { break; }
    }

    edit.Draw ();
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
