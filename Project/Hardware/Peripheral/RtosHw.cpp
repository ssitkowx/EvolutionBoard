///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include "RtosHw.h"
#include "LoggerHw.h"
#include "freertos/semphr.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

SemaphoreHandle_t TouchSemaphoreHandle;
SemaphoreHandle_t WeatherMeasureSemaphoreHandle;
SemaphoreHandle_t WeatherMeasureUpdateSemaphoreHandle;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RtosHw::RtosHw ()
{
    LOG (MODULE, "Init.");

    TouchSemaphoreHandle = xSemaphoreCreateBinary ();
    if (TouchSemaphoreHandle == NULL) { LOGE (MODULE, "Could't allocate TouchSemaphoreHandle."); }

    WeatherMeasureSemaphoreHandle = xSemaphoreCreateBinary ();
    if (WeatherMeasureSemaphoreHandle == NULL) { LOGE (MODULE, "Could't allocate WeatherMeasureSemaphoreHandle."); }

    WeatherMeasureUpdateSemaphoreHandle = xSemaphoreCreateBinary ();
    if (WeatherMeasureUpdateSemaphoreHandle == NULL) { LOGE (MODULE, "Could't allocate WeatherMeasureUpdateSemaphoreHandle."); }
}

RtosHw::~RtosHw ()
{
    LOG (MODULE, "Deinit.");
}

bool RtosHw::TakeSemaphore (std::string_view v_name)
{
    if (strcmp ("TakeTouchSemaphore"               , v_name.data ()) == ZERO) { return TakeTouchSemaphore (); }
    if (strcmp ("TakeWeatherMeasureSemaphore"      , v_name.data ()) == ZERO) { return TakeWeatherMeasureSemaphore (); }
    if (strcmp ("TakeWeatherMeasureUpdateSemaphore", v_name.data ()) == ZERO) { return TakeWeatherMeasureUpdateSemaphore (); }
    return false;
}

bool RtosHw::GiveSemaphore (std::string_view v_name)
{
    if (strcmp ("GiveWeatherMeasureUpdateSemaphore", v_name.data ()) == ZERO) { return GiveWeatherMeasureUpdateSemaphore (); }
    return false;
}

bool RtosHw::GiveSemaphoreFromISR (std::string_view v_name)
{
    if (strcmp ("GiveTouchSemaphoreFromISR"         , v_name.data ()) == ZERO) { return GiveTouchSemaphoreFromISR (); }
    if (strcmp ("GiveWeatherMeasureSemaphoreFromISR", v_name.data ()) == ZERO) { return GiveWeatherMeasureSemaphoreFromISR (); }
    return false;
}

bool RtosHw::GiveWeatherMeasureUpdateSemaphore (void)
{
    return (xSemaphoreGive (WeatherMeasureUpdateSemaphoreHandle) == pdTRUE) ? true : false;
}

bool RtosHw::GiveTouchSemaphoreFromISR (void)
{
    static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    return (xSemaphoreGiveFromISR (TouchSemaphoreHandle, &xHigherPriorityTaskWoken) == pdTRUE) ? true : false;
}

bool RtosHw::GiveWeatherMeasureSemaphoreFromISR (void)
{
    static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    return (xSemaphoreGiveFromISR (WeatherMeasureSemaphoreHandle, &xHigherPriorityTaskWoken) == pdTRUE) ? true : false;
}

bool RtosHw::TakeTouchSemaphore (void)
{
    return (xSemaphoreTake (TouchSemaphoreHandle, (TickType_t)ETick::ePortMinDelay) == pdTRUE) ? true : false;
}

bool RtosHw::TakeWeatherMeasureSemaphore (void)
{
    return (xSemaphoreTake (WeatherMeasureSemaphoreHandle, (TickType_t)ETick::ePortMaxDelay) == pdTRUE) ? true : false;
}

bool RtosHw::TakeWeatherMeasureUpdateSemaphore (void)
{
    return (xSemaphoreTake (WeatherMeasureUpdateSemaphoreHandle, (TickType_t)ETick::ePortMinDelay) == pdTRUE) ? true : false;
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
