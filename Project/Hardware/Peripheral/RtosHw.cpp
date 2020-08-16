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

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RtosHw::RtosHw ()
{
    LOG (MODULE, "Init.");

    TouchSemaphoreHandle = xSemaphoreCreateBinary ();
    if (TouchSemaphoreHandle == NULL) { LOGE (MODULE, "Could't allocate ReqAzureDataUpdateeSemaphoreHandle./n"); }
}

RtosHw::~RtosHw ()
{
    LOG (MODULE, "Deinit.");
}

bool RtosHw::GiveSemaphoreFromISR (const std::string & v_name)
{
    if (strcmp ("GiveTouchSemaphoreFromISR", v_name.data ()) == ZERO) { return GiveTouchSemaphoreFromISR (); }

    return false;
}

bool RtosHw::TakeSemaphore (const std::string & v_name)
{
    if (strcmp ("TakeTouchSemaphore", v_name.data ()) == ZERO) { return TakeTouchSemaphore (); }

    return false;
}

bool RtosHw::GiveTouchSemaphoreFromISR (void)
{
    static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    return (xSemaphoreGiveFromISR (TouchSemaphoreHandle, &xHigherPriorityTaskWoken) == pdTRUE) ? true : false;
}

bool RtosHw::TakeTouchSemaphore (void)
{
    return (xSemaphoreTake (TouchSemaphoreHandle, (TickType_t)ETick::ePortMaxDelay) == pdTRUE) ? true : false;
}

uint32_t RtosHw::GetCurrentStackSize (const std::string & v_name)
{
    extern TaskHandle_t DisplayAndTouchTaskHandle;
    extern TaskHandle_t NetworkConnectionTaskHandle;
    
    if (strcmp (v_name.data (), "DisplayAndTouch"))    { return uxTaskGetStackHighWaterMark (DisplayAndTouchTaskHandle);   }
    if (strcmp (v_name.data (), "InternetConnection")) { return uxTaskGetStackHighWaterMark (NetworkConnectionTaskHandle); }
    
    LOGE (MODULE, "Couldn't find task.");
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
