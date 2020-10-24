///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "RtosHw.h"
#include <stdint.h>
#include "GpioHw.h"
#include "WiFiHw.h"
#include "FLashHw.h"
#include "TouchHw.h"
#include "Settings.h"
#include "LoggerHw.h"
#include "BitmapHw.h"
#include "DisplayHw.h"
#include "BaseWindow.h"
#include "SystemTimeHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static constexpr char * MODULE = (char *)"MainCppHw";

TaskHandle_t DisplayWithTouchTaskHandle;
TaskHandle_t NetworkConnectionTaskHandle;
TaskHandle_t MemoryStatisticsTaskHandle;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

extern "C"
{
    void DisplayWithTouchProcess    (void * v_params);
    void InternetConnectionProcess (void * v_params);
    void MemoryStatisticsProcess   (void * v_params);

    void MainCppHw (void)
    {
        FlashHw flashHw;

        static RtosHw rtosHw;
        SET_RTOS_INST(&rtosHw);

        static SystemTimeHw systemTimeHw;
        SET_SYSTEM_TIME_INST(&systemTimeHw);

        Rtos::GetInstance ()->TaskCreate (DisplayWithTouchProcess,
                                          "DisplayWithTouch",
                                          THIRTY_THOUSAND_BYTES,
                                          static_cast <uint32_t> (RtosHw::EThreadPriority::eNormal),
                                          DisplayWithTouchTaskHandle);

        Rtos::GetInstance ()->TaskCreate (InternetConnectionProcess,
                                          "InternetConnection",
                                          FIVE_THOUSAND_BYTES,
                                          static_cast <uint32_t> (RtosHw::EThreadPriority::eAboveNormal),
                                          NetworkConnectionTaskHandle);


        Rtos::GetInstance ()->TaskCreate (MemoryStatisticsProcess,
                                          "MemoryStatistics",
                                          THIRTY_THOUSAND_BYTES,
                                          static_cast <uint32_t> (RtosHw::EThreadPriority::eLow),
                                          MemoryStatisticsTaskHandle);
    }

    void DisplayWithTouchProcess (void * v_params)
    {
        GpioHw gpioHw;
        DisplayHw::Config_t displayConfig;
        displayConfig.Dimension.Width   = Settings::GetInstance ().Lcd.Width;
        displayConfig.Dimension.Height  = Settings::GetInstance ().Lcd.Height;
        displayConfig.LinesPerTransfer  = Settings::GetInstance ().Lcd.LinesPerTransfer;
        DisplayHw displayHw (displayConfig, gpioHw);

        Touch::Config touchConfig;
        touchConfig.Histeresis          = TWO;
        touchConfig.Time.PressedMax     = FOUR;    // InterruptInSeconds * PressedMax
        touchConfig.Time.ReleasedMax    = EIGHT;

        TouchHw::Coefficients touchCoefficient;
        touchCoefficient.Constant       = ONE_HUNDRED_TWENTY_EIGHT;
        touchCoefficient.Width          = TWO;
        touchCoefficient.Length         = 2.67;

        TimerHw::Config timerTouchConfig;
        timerTouchConfig.eTimer         = Timer::ETimer::e0;
        timerTouchConfig.Divider        = SIXTEEN;
        timerTouchConfig.InterruptInSec = 0.02;

        TouchHw touchHw (timerTouchConfig, touchCoefficient, touchConfig, displayHw);

        NumericKeyboard::Configuration config;
        config.KeyboardStart.X          = EIGHTY;
        config.KeyboardStart.Y          = FORTY;
        config.BitmapSpacing.X          = FIVE;
        config.BitmapSpacing.Y          = FIVE;

        NumericKeyboard numericKeyboard (config, displayHw);
        BaseWindow      baseWindow      (displayHw, touchHw, numericKeyboard);

        //////////////////////// Touch ////////////////////

        while (true)
        {
            baseWindow.Process ();
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "DisplayAndTouchProcess() Deleted.");
    }

    void InternetConnectionProcess (void * v_params)
    {
        WiFiHw wifiHw;

        while (true)
        {
            Rtos::GetInstance ()->Delay (FIVE_HUNDRED);
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "InternetConnectionProcess() Deleted.");

    }

    void MemoryStatisticsProcess (void * v_params)
    {
        TimerHw::Config timerMemoryStatisticConfig;
        timerMemoryStatisticConfig.eTimer         = Timer::ETimer::e1;
        timerMemoryStatisticConfig.Divider        = SIXTEEN;
        timerMemoryStatisticConfig.InterruptInSec = TEN;

        TimerHw timerMemoryStatisticHw (timerMemoryStatisticConfig);

        while (true)
        {
            if (Rtos::GetInstance ()->TakeSemaphore ("TakeMemoryStatisticsSemaphore") == true)
            {
                LOGI (MODULE, "Heap left                    : %d", Rtos::GetInstance ()->GetCurrentHeapSize ());
                LOGI (MODULE, "DisplayAndTouch    stack left: %d", Rtos::GetInstance ()->GetCurrentStackSize ("DisplayAndTouch"));
                LOGI (MODULE, "InternetConnection stack left: %d", Rtos::GetInstance ()->GetCurrentStackSize ("InternetConnection"));
                LOGI (MODULE, "MemoryStatistics   stack left: %d", Rtos::GetInstance ()->GetCurrentStackSize ("MemoryStatistics"));
            }
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "GetMemoryStatisticsProcess() Deleted.");
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
