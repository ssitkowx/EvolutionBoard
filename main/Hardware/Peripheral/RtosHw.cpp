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

SemaphoreHandle_t AzureDataUpdateSemaphoreHandle;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RtosHw::RtosHw (void)
{
    LOG (MODULE, "Init");

    AzureDataUpdateSemaphoreHandle = xSemaphoreCreateBinary ();
    if (AzureDataUpdateSemaphoreHandle == NULL)
    {
        LOGE (MODULE, "Could't allocate ReqAzureDataUpdateeSemaphoreHandle");
    }
}

RtosHw::~RtosHw ()
{
    LOG (MODULE, "Deinit");
}

bool RtosHw::GiveAzureDataUpdateSemaphoreFromISR (void)
{
    static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    return (xSemaphoreGiveFromISR(AzureDataUpdateSemaphoreHandle, &xHigherPriorityTaskWoken) == pdTRUE) ? true : false;
}

bool RtosHw::TakeAzureDataUpdateSemaphore (void)
{
    return (xSemaphoreTake (AzureDataUpdateSemaphoreHandle, (TickType_t)ETick::ePortMaxDelay) == pdTRUE) ? true : false;
}

uint32_t RtosHw::TaskCreate (TaskFunctionType   v_taskFuncion,
                             const char * const v_taskName,
                             const uint32_t     v_stackDepth,
                             const uint32_t     v_priority,
                             TaskHandle         v_taskHandle)
{
    return xTaskCreate (v_taskFuncion, v_taskName, v_stackDepth, NULL, v_priority, NULL);
}

uint32_t RtosHw::GetCurrentHeapSize (void)
{
    return esp_get_free_heap_size ();
}

uint32_t RtosHw::GetCurrentStackSize (const char * v_taskName)
{
    extern TaskHandle_t MicorTigWelderTaskHandle;
    extern TaskHandle_t MicorTigAzureTaskHandle;
    
    if (strcmp (v_taskName, "MicorTigWelderComm"))
    {
        return uxTaskGetStackHighWaterMark (MicorTigWelderTaskHandle);
    }
    
    if (strcmp (v_taskName, "MicorTigAzureComm"))
    {
        return uxTaskGetStackHighWaterMark (MicorTigAzureTaskHandle);
    }
    
    LOGE (MODULE, "Couldn't find task");
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
