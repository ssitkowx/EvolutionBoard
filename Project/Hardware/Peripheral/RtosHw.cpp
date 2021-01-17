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
EventGroupHandle_t WeatherMeasureAndButtonsUpdatesEventGroupHandle;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RtosHw::RtosHw ()
{
    LOG (MODULE, "Init.");

    WeatherMeasureSemaphoreHandle = xSemaphoreCreateBinary ();
    if (WeatherMeasureSemaphoreHandle == NULL) { LOGE (MODULE, "Could't allocate WeatherMeasureSemaphoreHandle."); }

    WeatherMeasureAndButtonsUpdatesEventGroupHandle = xEventGroupCreate ();
    if (WeatherMeasureAndButtonsUpdatesEventGroupHandle == NULL) { LOGE (MODULE, "Could't allocate WeatherMeasureAndButtonsUpdatesEventGroupHandle."); }
}

RtosHw::~RtosHw ()
{
    LOG (MODULE, "Deinit.");
}

bool RtosHw::TakeSemaphore (std::string_view v_name)
{
    if (strcmp ("TakeWeatherMeasureSemaphore", v_name.data ()) == ZERO) { return TakeWeatherMeasureSemaphore (); }
    return false;
}

bool RtosHw::GiveSemaphoreFromISR (std::string_view v_name)
{
    if (strcmp ("GiveWeatherMeasureSemaphoreFromISR", v_name.data ()) == ZERO) { return GiveWeatherMeasureSemaphoreFromISR (); }
    return false;
}

bool RtosHw::GiveWeatherMeasureSemaphoreFromISR (void)
{
    static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    return (xSemaphoreGiveFromISR (WeatherMeasureSemaphoreHandle, &xHigherPriorityTaskWoken) == pdTRUE) ? true : false;
}

bool RtosHw::TakeWeatherMeasureSemaphore (void)
{
    return (xSemaphoreTake (WeatherMeasureSemaphoreHandle, (TickType_t)ETick::ePortMaxDelay) == pdTRUE) ? true : false;
}

void RtosHw::SetBitsEventGroup (std::string_view v_name, const EEventGroup v_eBit)
{
    if (strcmp ("WeatherMeasureAndButtonsUpdatesEventGroupHandle", v_name.data ()) == ZERO)
    {
        xEventGroupSetBits (WeatherMeasureAndButtonsUpdatesEventGroupHandle, static_cast <uint32_t>(v_eBit));
    }
}

void RtosHw::SetBitsEventGroupFromISR (std::string_view v_name, const EEventGroup v_eBit)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if (strcmp ("WeatherMeasureAndButtonsUpdatesEventGroupHandle", v_name.data ()) == ZERO)
    {
        xEventGroupSetBitsFromISR (WeatherMeasureAndButtonsUpdatesEventGroupHandle, static_cast <uint32_t>(v_eBit), &xHigherPriorityTaskWoken);
    }
}

void RtosHw::ClearBitsEventGroup (std::string_view v_name, const EEventGroup v_eBit)
{
    if (strcmp ("WeatherMeasureAndButtonsUpdatesEventGroupHandle", v_name.data ()) == ZERO)
    {
        xEventGroupClearBits (WeatherMeasureAndButtonsUpdatesEventGroupHandle, static_cast <uint32_t>(v_eBit));
    }
}

uint32_t RtosHw::WaitBitsEventGroup (std::string_view v_name)
{
    EventBits_t maskBits = ZERO;
    if (strcmp ("WeatherMeasureAndButtonsUpdatesEventGroupHandle", v_name.data ()) == ZERO)
    {
        maskBits = xEventGroupWaitBits (WeatherMeasureAndButtonsUpdatesEventGroupHandle,
                                        static_cast <uint32_t>(EEventGroup::eFirst) |
                                        static_cast <uint32_t>(EEventGroup::eSecond),
                                        pdFALSE,
                                        pdFALSE,
                                        (TickType_t)ETick::ePortMaxDelay);
    }

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
