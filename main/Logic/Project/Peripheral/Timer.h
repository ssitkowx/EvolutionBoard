/**
 * Project : Lorch - Presents MicroTIG data on Azure Cloud.
 *
 * \file Timer.h
 * \brief General class for Timer.
 * \author sylsit
 * \date 2020.01.24
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

/******************************************************************************
                                 VARIABLES
******************************************************************************/

class Timer
{
    public:
        enum class ETimer : uint8_t
        {
            eTim0,
            eTim1,
            eTim7,
            eTim14,
            eTim16,
            eTim17,
        };

        Timer () = default;
        virtual ~Timer () = default;

        virtual void     Start      (void)               = 0;
        virtual void     Stop       (void)               = 0;
        virtual void     StartIsr   (void)               = 0;
        virtual void     StopIsr    (void)               = 0;
        virtual void     Reset      (void)               = 0;
        virtual void     ResetIsr   (void)               = 0;

        virtual void     SetCounter (uint32_t v_counter) = 0;
        virtual uint32_t GetCounter (void)               = 0;

    protected:
        virtual void     init       (void)               = 0;
        virtual void     deInit     (void)               = 0;
};

/******************************************************************************
                                 FUNCTIONS
******************************************************************************/

/****************************** END OF FILE  *********************************/

