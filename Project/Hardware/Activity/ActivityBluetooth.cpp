///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include "BitmapId.h"
#include "ButtonsImages.h"
#include "WeatherBackground.h"
#include "ActivityBluetooth.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ActivityBluetooth::ActivityBluetooth (Touch<TouchHw>         & v_touch,
                                      Draftsman<DraftsmanHw> & v_draftsman,
                                      Resources              & v_resources) : touch      (v_touch),
                                                                              resources  (v_resources),
                                                                              background (v_draftsman),
                                                                              buttonDown (v_draftsman),
                                                                              buttonUp   (v_draftsman),
                                                                              edit       (v_draftsman)
{
    LOG (MODULE, "Init.");

    uint16_t xPos = FIFTEEN;
    uint16_t yPos = TWO_HUNDRED_SIXTY;

    background.Create <static_cast <uint16_t>(EBitmapId::eBleBackground)> (WeatherBackground, ZERO, ZERO);
    buttonDown.Create <static_cast <uint16_t>(EBitmapId::eBleButtonDown)> (BleButtonDown, xPos, yPos, true);
    buttonUp  .Create <static_cast <uint16_t>(EBitmapId::eBleButtonUp)  > (BleButtonUp  , xPos, yPos, true);

    Subscribe (background);
    Subscribe (buttonDown);
    Subscribe (buttonUp);
    Subscribe (edit);
}

void ActivityBluetooth::Process (void)
{
    static Bitmap::Coordinates coordinates;

    Touch<TouchHw>::EState eState = touch.Event ();
    if (eState == Touch<TouchHw>::EState::ePressed)
    {
        coordinates = touch.GetCoordinates ();
        buttonDown.Draw (static_cast <uint8_t> (EBitmapId::eBleButtonDown), coordinates);
    }
    else if (eState == Touch<TouchHw>::EState::eReleased)
    {
        buttonUp.Draw (static_cast <uint8_t> (EBitmapId::eBleButtonUp), coordinates);
        Rtos::GetInstance ()->SetBitsEventGroup ("SwitchToWeatherActivity");
    }
    else { }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
