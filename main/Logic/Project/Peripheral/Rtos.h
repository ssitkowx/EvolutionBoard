/**
 * Project : Lorch - Presents MicroTIG data on Azure Cloud.
 *
 * \file Rtos.h
 * \brief General class for rtos.
 * \author sylsit
 * \date 2020.02.17
 * \copyright 2018 Fideltronik R&D - all rights reserved.
 * \version File template version 12.2018
*/

#pragma once 

/******************************************************************************
                                 INCLUDES
******************************************************************************/

#include <stdint.h>

/******************************************************************************
                            MACROS/DEFINITIONS
******************************************************************************/

#define SET_RTOS_INST(INSTANCE) Rtos::SetInstance (INSTANCE);

/******************************************************************************
                                 VARIABLES
******************************************************************************/

class Rtos
{
    private:
        static Rtos * instance;

    public:
        static void      SetInstance                         (Rtos * v_instance) { instance = v_instance; }
        static Rtos *    GetInstance                         (void) { return instance; }

        typedef void * TaskHandle;
        typedef void (* TaskFunctionType)(void *);

        virtual ~Rtos () = default;

        virtual bool     GiveAzureDataUpdateSemaphoreFromISR (void)                             = 0;
        virtual bool     TakeAzureDataUpdateSemaphore        (void)                             = 0;

        virtual uint32_t TaskCreate                          (TaskFunctionType   v_taskFuncion,
                                                              const char * const v_taskName,
                                                              const uint32_t     v_stackDepth,
                                                              const uint32_t     v_priority,
                                                              TaskHandle         v_taskHandle)  = 0;

        virtual uint32_t GetCurrentHeapSize                  (void)                             = 0;
        virtual uint32_t GetCurrentStackSize                 (const char * v_taskName)          = 0;
};

/******************************************************************************
                                 FUNCTIONS
******************************************************************************/

/****************************** END OF FILE  *********************************/

