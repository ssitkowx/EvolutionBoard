///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include "esp_err.h"
#include "TimerHw.h"
#include "Settings.h"
#include "LoggerHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void IRAM_ATTR timer0Isr (void * v_params)
{
    if ((TIMERG0.int_st_timers.val & BIT(TIMER_0)) && TIMER_0 == TIMER_0)
    {
        TIMERG0.int_clr_timers.t0                  = ONE;
        TIMERG0.hw_timer [TIMER_0].config.alarm_en = ONE;
    }
    else if ((TIMERG0.int_st_timers.val & BIT (TIMER_1)) && TIMER_1 == TIMER_1)
    {
        TIMERG0.int_clr_timers.t1 = ONE;
    }

    Rtos::GetInstance()->GiveAzureDataUpdateSemaphoreFromISR ();
}

TimerHw::TimerHw  (Timer::ETimer v_eTimer)
{
    setTimerConfig (v_eTimer);
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
    LOG             (MODULE, "Start");
    ESP_ERROR_CHECK (timer_start (group, number));
}

void TimerHw::Stop (void)
{
    LOG             (MODULE, "Stop");
    ESP_ERROR_CHECK (timer_pause (group, number));
}

void TimerHw::StartIsr (void)
{
    ESP_ERROR_CHECK (timer_enable_intr  (group, number));
    ESP_ERROR_CHECK (timer_isr_register (group,
                                         number,
                                         timer0Isr, (void *) number,
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
    LOG (MODULE, "Init./n");
    
    timer_config_t config;
    config.divider     = Settings::GetInstance ().Timer.TimerDivider;
    config.counter_dir = TIMER_COUNT_UP;
    config.counter_en  = TIMER_PAUSE;
    config.alarm_en    = TIMER_ALARM_EN;
    config.intr_type   = TIMER_INTR_LEVEL;
    config.auto_reload = 1;

    ESP_ERROR_CHECK (timer_init              (group, number, &config));
    ESP_ERROR_CHECK (timer_set_counter_value (group, number, 0x0000000000ULL));

    ESP_ERROR_CHECK (timer_set_alarm_value   (group, number, Settings::GetInstance ().Timer.TimerInteruptInSeconds * TIMER_BASE_CLK /  Settings::GetInstance ().Timer.TimerDivider));
    ESP_ERROR_CHECK (timer_enable_intr       (group, number));
    ESP_ERROR_CHECK (timer_isr_register      (group, number, timer0Isr, (void *) number, ESP_INTR_FLAG_IRAM, NULL));
}

void TimerHw::deInit (void)
{
    LOG (MODULE, "Deinit./n");
}

void TimerHw::setTimerConfig (Timer::ETimer v_eTimer)
{
    switch (v_eTimer)
    {
        case Timer::ETimer::eTim0:
        {
            number = TIMER_0;
            group  = TIMER_GROUP_0;
            break;
        }
        case Timer::ETimer::eTim1:
        {
            number = TIMER_1;
            group  = TIMER_GROUP_1;
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