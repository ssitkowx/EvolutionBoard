#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Timer.h"
#include <stdint.h>
#include "driver/timer.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class TimerHw final : public Timer<TimerHw>
{
    static constexpr char * MODULE = (char *)"TimerHw";

    public:
        struct Config
        {
            double Divider;
            double InterruptInSec;
            ETimer eTimer;
        };

        TimerHw  (const Config v_config);
        ~TimerHw ();

        void     Start          (void);
        void     Stop           (void);
        void     StartIsr       (void);
        void     StopIsr        (void);
        void     Reset          (void);
        void     ResetIsr       (void);
        uint32_t GetCounter     (void)               { return 0; }
        void     SetCounter     (uint32_t v_counter) {}

    protected:
        void     init           (void);
        void     deInit         (void);
    
    private:
        const Config  config;
        timer_idx_t   number;
        timer_group_t group;

        void    setTimerConfig  (Timer<TimerHw>::ETimer v_eTimerNum);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
