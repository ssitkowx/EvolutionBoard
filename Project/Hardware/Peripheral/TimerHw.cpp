///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include <esp_err.h>
#include "TimerHw.h"
#include "Settings.h"
#include "LoggerHw.h"
#include <esp_bit_defs.h>

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void IRAM_ATTR timerIsr (void * v_params)
{
    if ((TIMERG0.int_st_timers.val & BIT(TIMER_0)) && TIMER_0 == TIMER_0)
    {
        TIMERG0.int_clr_timers.t0                  = ONE;
        TIMERG0.hw_timer [TIMER_0].config.alarm_en = ONE;
        //Rtos::GetInstance ()->GiveSemaphoreFromISR ("GiveWeatherMeasureSemaphoreFromISR");    // this can be touch
    }
    else if ((TIMERG0.int_st_timers.val & BIT (TIMER_1)) && TIMER_1 == TIMER_1)
    {
        TIMERG0.int_clr_timers.t1                  = ONE;
        TIMERG0.hw_timer [TIMER_1].config.alarm_en = ONE;
        Rtos::GetInstance()->GiveSemaphoreFromISR ("GiveWeatherMeasureSemaphoreFromISR");
    }
}

TimerHw::TimerHw  (const Config v_config) : config (v_config)
{
    LOG            (MODULE, "Init.");
    setTimerConfig (config.eTimer);
    init           ();
    Start          ();
}

TimerHw::~TimerHw ()
{
    Stop   ();
    deInit ();
}

void TimerHw::Start (void)
{
    LOG             (MODULE, "Start.");
    ESP_ERROR_CHECK (timer_start (group, number));
}

void TimerHw::Stop (void)
{
    LOG             (MODULE, "Stop.");
    ESP_ERROR_CHECK (timer_pause (group, number));
}

void TimerHw::StartIsr (void)
{
    ESP_ERROR_CHECK (timer_enable_intr  (group, number));
    ESP_ERROR_CHECK (timer_isr_register (group,
                                         number,
                                         timerIsr, (void *) number,
                                         ESP_INTR_FLAG_IRAM,
                                         NULL));
    
    ESP_ERROR_CHECK (timer_start (group, number));
}

void TimerHw::StopIsr (void)
{
    ESP_ERROR_CHECK (timer_disable_intr (group, number));
}

void TimerHw::Reset (void)
{
    Stop  ();
    Start ();
}

void TimerHw::ResetIsr (void)
{
	StopIsr  ();
	StartIsr ();
}

void TimerHw::init (void)
{
    LOG (MODULE, "Init.");
    
    timer_config_t timerConfig;
    timerConfig.divider     = config.Divider;
    timerConfig.counter_dir = TIMER_COUNT_UP;
    timerConfig.counter_en  = TIMER_PAUSE;
    timerConfig.alarm_en    = TIMER_ALARM_EN;
    timerConfig.intr_type   = TIMER_INTR_LEVEL;
    timerConfig.auto_reload = static_cast<timer_autoreload_t>(ONE);

    ESP_ERROR_CHECK (timer_init              (group, number, &timerConfig));
    ESP_ERROR_CHECK (timer_set_counter_value (group, number, 0x0000000000ULL));

    ESP_ERROR_CHECK (timer_set_alarm_value   (group, number, config.InterruptInSec * TIMER_BASE_CLK /  config.Divider));
    ESP_ERROR_CHECK (timer_enable_intr       (group, number));
    ESP_ERROR_CHECK (timer_isr_register      (group, number, timerIsr, (void *)number, ESP_INTR_FLAG_IRAM, NULL));
}

void TimerHw::deInit (void)
{
    LOG (MODULE, "Deinit.\n");
}

void TimerHw::setTimerConfig (ETimer v_eTimer)
{
    switch (v_eTimer)
    {
        case Timer<TimerHw>::ETimer::e0:
        {
            number = TIMER_0;
            group  = TIMER_GROUP_0;
            break;
        }
        case Timer<TimerHw>::ETimer::e1:
        {
            number = TIMER_1;
            group  = TIMER_GROUP_0;
            break;
        }
        default:
        {
            LOGE (MODULE, "Unknown timer");
            break;
        }
    };
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
