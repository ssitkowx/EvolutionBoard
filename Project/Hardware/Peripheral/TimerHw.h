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

class TimerHw final : public Timer
{
    static constexpr char * MODULE = (char *)"TimerHw";

    public:
        TimerHw  (Timer::ETimer v_eTimer);
        ~TimerHw ();

        void     Start          (void)               override;
        void     Stop           (void)               override;
        void     StartIsr       (void)               override;
        void     StopIsr        (void)               override;
        void     Reset          (void)               override;
        void     ResetIsr       (void)               override;
        uint32_t GetCounter     (void)               override { return 0; }
        void     SetCounter     (uint32_t v_counter) override {}

    protected:
        void     init           (void)               override;
        void     deInit         (void)               override;
    
    private:
        timer_idx_t             number;
        timer_group_t           group;

        void    setTimerConfig  (Timer::ETimer v_eTimer);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////