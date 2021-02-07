///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include "RtosHw.h"
#include "LoggerHw.h"
#include <freertos/semphr.h>
#include <freertos/event_groups.h>

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

SemaphoreHandle_t  WeatherMeasureSemaphoreHandle;
EventGroupHandle_t SystemEventGroupHandle;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RtosHw::RtosHw ()
{
    LOG (MODULE, "Init.");

    SystemEventGroupHandle = xEventGroupCreate ();
    if (SystemEventGroupHandle == NULL) { LOGE (MODULE, "Could't allocate SystemEventGroupHandle."); }

    WeatherMeasureSemaphoreHandle = xSemaphoreCreateBinary ();
    if (WeatherMeasureSemaphoreHandle == NULL) { LOGE (MODULE, "Could't allocate WeatherMeasureSemaphoreHandle."); }
}

RtosHw::~RtosHw ()
{
    LOG (MODULE, "Deinit.");
}

bool RtosHw::TakeSemaphore (std::string_view v_name)
{

    if (strcmp ("TakeWeatherMeasureSemaphore", v_name.data ()) == ZERO) { return (xSemaphoreTake (WeatherMeasureSemaphoreHandle, (TickType_t)ETick::ePortMaxDelay) == pdTRUE) ? true : false; }
    return false;
}

bool RtosHw::GiveSemaphoreFromISR (std::string_view v_name)
{
    static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if (strcmp ("GiveWeatherMeasureSemaphoreFromISR", v_name.data ()) == ZERO) { return (xSemaphoreGiveFromISR (WeatherMeasureSemaphoreHandle, &xHigherPriorityTaskWoken) == pdTRUE) ? true : false; }
    return false;
}

void RtosHw::SetBitsEventGroup (std::string_view v_name)
{
    if      (strcmp ("SwitchToWeatherActivity"  , v_name.data ()) == ZERO) { xEventGroupSetBits (SystemEventGroupHandle, static_cast <uint32_t>(EEventId::eSwitchToWeatherActivity  )); }
    else if (strcmp ("SwitchToBluetoothActivity", v_name.data ()) == ZERO) { xEventGroupSetBits (SystemEventGroupHandle, static_cast <uint32_t>(EEventId::eSwitchToBluetoothActivity)); }
    else if (strcmp ("WeatherMeasureUpdated"    , v_name.data ()) == ZERO) { xEventGroupSetBits (SystemEventGroupHandle, static_cast <uint32_t>(EEventId::eWeatherMeasureUpdated    )); }
    else if (strcmp ("BluetoothDataUpdated"     , v_name.data ()) == ZERO) { xEventGroupSetBits (SystemEventGroupHandle, static_cast <uint32_t>(EEventId::eBluetoothDataUpdated     )); }
}

void RtosHw::ClearBitsEventGroup (std::string_view v_name)
{
    if      (strcmp ("SwitchToWeatherActivity"  , v_name.data ()) == ZERO) { xEventGroupClearBits (SystemEventGroupHandle, static_cast <uint32_t>(EEventId::eSwitchToWeatherActivity  )); }
    else if (strcmp ("SwitchToBluetoothActivity", v_name.data ()) == ZERO) { xEventGroupClearBits (SystemEventGroupHandle, static_cast <uint32_t>(EEventId::eSwitchToBluetoothActivity)); }
    else if (strcmp ("WeatherMeasureUpdated"    , v_name.data ()) == ZERO) { xEventGroupClearBits (SystemEventGroupHandle, static_cast <uint32_t>(EEventId::eWeatherMeasureUpdated    )); }
    else if (strcmp ("BluetoothDataUpdated"     , v_name.data ()) == ZERO) { xEventGroupClearBits (SystemEventGroupHandle, static_cast <uint32_t>(EEventId::eBluetoothDataUpdated     )); }
}

uint32_t RtosHw::WaitBitsEventGroup (void)
{
    EventBits_t maskBits = xEventGroupWaitBits (SystemEventGroupHandle, static_cast <uint32_t>(EEventId::eSwitchToWeatherActivity  ) |
                                                                        static_cast <uint32_t>(EEventId::eSwitchToBluetoothActivity) |
                                                                        static_cast <uint32_t>(EEventId::eWeatherMeasureUpdated    ) |
                                                                        static_cast <uint32_t>(EEventId::eBluetoothDataUpdated     ),
                                                                        pdFALSE,
                                                                        pdFALSE,
                                                                        (TickType_t)ETick::ePortMinDelay);
    return maskBits;
}

uint32_t RtosHw::GetCurrentStackSize (std::string_view v_name)
{
    extern TaskHandle_t BluetoothTaskHandle;
    extern TaskHandle_t WeatherMeasureTaskHandle;
    extern TaskHandle_t DisplayAndTouchTaskHandle;

    if (strcmp (v_name.data (), "BluetoothProcess"))       { return uxTaskGetStackHighWaterMark (BluetoothTaskHandle);       }
    if (strcmp (v_name.data (), "WeatherMeasureProcess"))  { return uxTaskGetStackHighWaterMark (WeatherMeasureTaskHandle);  }
    if (strcmp (v_name.data (), "DisplayAndTouchProcess")) { return uxTaskGetStackHighWaterMark (DisplayAndTouchTaskHandle); }
    
    LOGE (MODULE, "Couldn't find task.");
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
