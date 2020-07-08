#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#define SET_RTOS_INST(INSTANCE) Rtos::SetInstance (INSTANCE);

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Rtos
{
    private:
        static Rtos * instance;

    public:
        typedef void * TaskHandle;
        typedef void (* TaskFunctionType)(void *);

        static void      SetInstance          (Rtos * v_instance) { instance = v_instance; }
        static Rtos *    GetInstance          (void) { return instance; }

        virtual ~Rtos () = default;

        virtual void     Delay                (const uint32_t v_ms)              = 0;
        //virtual bool     GiveSemaphoreFromISR (void)                             = 0;
        //virtual bool     TakeSemaphore        (void)                             = 0;

        virtual uint32_t GetCurrentHeapSize   (void)                             = 0;
        virtual uint32_t GetCurrentStackSize  (const char * v_taskName)          = 0;
        virtual uint32_t TaskCreate           (TaskFunctionType   v_taskFuncion,
                                               const char * const v_taskName,
                                               const uint32_t     v_stackDepth,
                                               const uint32_t     v_priority,
                                               TaskHandle         v_taskHandle)  = 0;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

