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
SemaphoreHandle_t MemoryStatisticsSemaphoreHandle;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RtosHw::RtosHw ()
{
    LOG (MODULE, "Init.");

    TouchSemaphoreHandle = xSemaphoreCreateBinary ();
    if (TouchSemaphoreHandle            == NULL) { LOGE (MODULE, "Could't allocate TouchSemaphoreHandle."); }

    MemoryStatisticsSemaphoreHandle = xSemaphoreCreateBinary ();
    if (MemoryStatisticsSemaphoreHandle == NULL) { LOGE (MODULE, "Could't allocate MemoryStatisticsSemaphoreHandle."); }
}

RtosHw::~RtosHw ()
{
    LOG (MODULE, "Deinit.");
}

bool RtosHw::GiveSemaphoreFromISR (const std::string & v_name)
{
    if (strcmp ("GiveTouchSemaphoreFromISR"           , v_name.data ()) == ZERO) { return GiveTouchSemaphoreFromISR (); }
    if (strcmp ("GiveMemoryStatisticsSemaphoreFromISR", v_name.data ()) == ZERO) { return GiveMemoryStatisticsSemaphoreFromISR (); }
    return false;
}

bool RtosHw::TakeSemaphore (const std::string & v_name)
{
    if (strcmp ("TakeTouchSemaphore"           , v_name.data ()) == ZERO) { return TakeTouchSemaphore (); }
    if (strcmp ("TakeMemoryStatisticsSemaphore", v_name.data ()) == ZERO) { return TakeMemoryStatisticsSemaphore (); }
    return false;
}

bool RtosHw::GiveTouchSemaphoreFromISR (void)
{
    static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    return (xSemaphoreGiveFromISR (TouchSemaphoreHandle, &xHigherPriorityTaskWoken) == pdTRUE) ? true : false;
}

bool RtosHw::GiveMemoryStatisticsSemaphoreFromISR (void)
{
    static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    return (xSemaphoreGiveFromISR (MemoryStatisticsSemaphoreHandle, &xHigherPriorityTaskWoken) == pdTRUE) ? true : false;
}

bool RtosHw::TakeTouchSemaphore (void)
{
    return (xSemaphoreTake (TouchSemaphoreHandle, (TickType_t)ETick::ePortMaxDelay) == pdTRUE) ? true : false;
}

bool RtosHw::TakeMemoryStatisticsSemaphore (void)
{
    return (xSemaphoreTake (MemoryStatisticsSemaphoreHandle, (TickType_t)ETick::ePortMaxDelay) == pdTRUE) ? true : false;
}

uint32_t RtosHw::GetCurrentStackSize (const std::string & v_name)
{
    extern TaskHandle_t DisplayAndTouchTaskHandle;
    extern TaskHandle_t NetworkConnectionTaskHandle;
    extern TaskHandle_t MemoryStatisticsTaskHandle;
    
    if (strcmp (v_name.data (), "DisplayAndTouch"))    { return uxTaskGetStackHighWaterMark (DisplayAndTouchTaskHandle);   }
    if (strcmp (v_name.data (), "InternetConnection")) { return uxTaskGetStackHighWaterMark (NetworkConnectionTaskHandle); }
    if (strcmp (v_name.data (), "MemoryStatistics"))   { return uxTaskGetStackHighWaterMark (MemoryStatisticsTaskHandle);  }
    
    LOGE (MODULE, "Couldn't find task.");
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
