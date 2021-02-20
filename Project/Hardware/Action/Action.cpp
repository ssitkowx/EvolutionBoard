///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "RtosHw.h"
#include "Action.h"
#include "ActionId.h"
#include "SystemEvents.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Action::Action (Touch <TouchHw>        & v_touch,
                Draftsman<DraftsmanHw> & v_draftsman,
                Resources              & v_resources) : draftsman         (v_draftsman),
                                                        resources         (v_resources),
                                                        weatherActivity   (v_touch, v_draftsman, v_resources),
                                                        bluetoothActivity (v_touch, v_draftsman, v_resources)
{
    SystemEvents::GetInstance ().CircBuf.Add ((uint8_t)(EActionId::eBackButtonUp));
}

void Action::Process (void)
{
    if (SystemEvents::GetInstance ().CircBuf.IsEmpty () == false)
    {
        uint16_t eventId = SystemEvents::GetInstance ().CircBuf.Remove ();
        switch (eventId)
        {
            case (uint16_t)EActionId::eBackButtonUp:
            {
                currentActivity = &weatherActivity;
                currentActivity->Start ();
                break;
            }
            case (uint16_t)EActionId::eBleButtonUp:
            {
                currentActivity = &bluetoothActivity;
                currentActivity->Start ();
                break;
            }
            case (uint16_t)EActionId::eSendButtonUp:
            {
                break;
            }
            case (uint16_t)EActionId::eBleUpdated:
            case (uint16_t)EActionId::eWeatherUpdated:
            {
                currentActivity->Update ();
                break;
            }
        }
    }

    currentActivity->Process ();
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
