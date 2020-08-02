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

SemaphoreHandle_t TouchUpdateSemaphoreHandle;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RtosHw::RtosHw ()
{
    LOG (MODULE, "Init.");

    TouchUpdateSemaphoreHandle = xSemaphoreCreateBinary ();
    if (TouchUpdateSemaphoreHandle == NULL) { LOGE (MODULE, "Could't allocate ReqAzureDataUpdateeSemaphoreHandle./n"); }
}

RtosHw::~RtosHw ()
{
    LOG (MODULE, "Deinit.");
}

bool RtosHw::GiveSemaphoreFromISR (const std::string & v_name)
{
    if (strcmp ("GiveTouchUpdateSemaphoreFromISR", v_name.data ()) == ZERO) { return GiveTouchUpdateSemaphoreFromISR (); }

    return false;
}

bool RtosHw::TakeSemaphore (const std::string & v_name)
{
    if (strcmp ("TakeTouchUpdateSemaphore", v_name.data ()) == ZERO) { return TakeTouchUpdateSemaphore (); }

    return false;
}

bool RtosHw::GiveTouchUpdateSemaphoreFromISR (void)
{
    static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    return (xSemaphoreGiveFromISR (TouchUpdateSemaphoreHandle, &xHigherPriorityTaskWoken) == pdTRUE) ? true : false;
}

bool RtosHw::TakeTouchUpdateSemaphore (void)
{
    return (xSemaphoreTake (TouchUpdateSemaphoreHandle, (TickType_t)ETick::ePortMaxDelay) == pdTRUE) ? true : false;
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
