///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "RtosHw.h"
#include "Action.h"

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
    Rtos::GetInstance ()->SetBitsEventGroup ("SwitchToWeatherActivity");
}

void Action::Process (void)
{
    const uint32_t event  = Rtos::GetInstance ()->WaitBitsEventGroup ();
    if ((event & (uint32_t)RtosHw::EEventId::eSwitchToWeatherActivity) != ZERO)
    {
        currentActivity = &weatherActivity;
        currentActivity->Start ();
        currentActivity->Update ();
        Rtos::GetInstance ()->ClearBitsEventGroup ("SwitchToWeatherActivity");
    }
    else if ((event & (uint32_t)RtosHw::EEventId::eSwitchToBluetoothActivity) != ZERO)
    {
        currentActivity = &bluetoothActivity;
        currentActivity->Start ();
        currentActivity->Update ();
        Rtos::GetInstance ()->ClearBitsEventGroup ("SwitchToBluetoothActivity");
    }
    else if ((event & (uint32_t)RtosHw::EEventId::eWeatherMeasureUpdated) != ZERO)
    {
        currentActivity->Update ();
        Rtos::GetInstance ()->ClearBitsEventGroup ("WeatherMeasureUpdated");
    }
    else if ((event & (uint32_t)RtosHw::EEventId::eBluetoothDataUpdated) != ZERO)
    {
        currentActivity->Update ();
        Rtos::GetInstance ()->ClearBitsEventGroup ("BluetoothDataUpdated");
    }

    currentActivity->Process ();
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
