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
    SystemEvents::GetInstance ().CircBuf.Push ((uint8_t)(EActionId::eBButtonUp));
}

void Action::Process (void)
{
    if (SystemEvents::GetInstance ().CircBuf.IsEmpty () == false)
    {
        uint16_t eventId = SystemEvents::GetInstance ().CircBuf.Pop ();
        switch (eventId)
        {
            case static_cast<uint16_t>(EActionId::eBButtonUp):
            {
                currentActivity = &weatherActivity;
                currentActivity->Start ();
                break;
            }
            case static_cast<uint16_t>(EActionId::eBleButtonUp):
            {
                currentActivity = &bluetoothActivity;
                currentActivity->Start ();
                break;
            }
            case static_cast<uint16_t>(EActionId::eSButtonUp):
            {
                break;
            }
            case static_cast<uint16_t>(EActionId::eRButtonDown):
            case static_cast<uint16_t>(EActionId::eAButtonDown):
            case static_cast<uint16_t>(EActionId::eXButtonDown):
            case static_cast<uint16_t>(EActionId::eZButtonDown):
            case static_cast<uint16_t>(EActionId::eBleUpdated):
            case static_cast<uint16_t>(EActionId::eWeatherUpdated):
            {
                currentActivity->Update (eventId);
                break;
            }
        }
    }

    currentActivity->Process ();
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
