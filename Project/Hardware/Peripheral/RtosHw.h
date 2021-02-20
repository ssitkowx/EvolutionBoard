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
            e0 = ZERO,
            e1 = ONE
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

        RtosHw ();
        ~RtosHw ();

        void     DelayInMs                (const uint32_t v_ms)           override { vTaskDelay (v_ms / portTICK_RATE_MS); }
        bool     TakeSemaphore            (std::string_view v_name)       override;
        bool     GiveSemaphoreFromISR     (std::string_view v_name)       override;
        uint32_t GetCurrentHeapSize       (void)                          override { return esp_get_free_heap_size ();     }
        uint32_t GetCurrentStackSize      (std::string_view v_name)       override;
        uint32_t TaskCreate               (TaskFunctionType v_taskFuncion,
                                           std::string_view v_taskName,
                                           const uint32_t   v_stackDepth,
                                           const uint32_t   v_priority,
                                           TaskHandle       v_taskHandle) override { return xTaskCreate (v_taskFuncion, v_taskName.data(), v_stackDepth, NULL, v_priority, NULL); }
    private:
        enum class ETick : uint32_t
        {
            ePortMinDelay = ZERO,
            ePortMaxDelay = portMAX_DELAY
        };
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
