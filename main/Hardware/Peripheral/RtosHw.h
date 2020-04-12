#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include "Utils.h"
#include <stdint.h>
#include "esp_task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class RtosHw final : public Rtos
{
    static constexpr char * MODULE = (char *)"RtosHw";

    public:
        enum class ECpuCore : uint32_t
        {
            e0 = 0,
            e1 = 1
        };

        enum class EThreadPriority : uint32_t
        {
            eIdle,
            eLow,
            eBelowNormal,
            eNormal,
            eAboveNormal,
            eBelowHigh,
            eHight,
            eAboveHight,
            eBelowRealtime,
            eRealTime,
            eBelowMax      = ESP_TASK_PRIO_MAX - ONE,
            eMax           = ESP_TASK_PRIO_MAX,
        };

        RtosHw (void);
        ~RtosHw (void);

        bool     GiveAzureDataUpdateSemaphoreFromISR (void)                             override;
        bool     TakeAzureDataUpdateSemaphore        (void)                             override;

        uint32_t TaskCreate                          (TaskFunctionType   v_taskFuncion,
                                                      const char * const v_taskName,
                                                      const uint32_t     v_stackDepth,
                                                      const uint32_t     v_priority,
                                                      TaskHandle         v_taskHandle)  override;

        uint32_t GetCurrentHeapSize                  (void)                             override;
        uint32_t GetCurrentStackSize                 (const char * v_taskName)          override;

    private:
        enum class ETick : uint32_t
        {
            ePortMinDelay = 0,
            ePortMaxDelay = portMAX_DELAY
        };
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
