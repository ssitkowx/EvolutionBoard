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
#include "HttpClientHw.h"
#include "WeatherMeasureComm.h"
#include "WeatherMeasureParser.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static constexpr char * MODULE = (char *)"MainCppHw";

TaskHandle_t WeatherMeasureTaskHandle;
TaskHandle_t DisplayWithTouchTaskHandle;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

extern "C"
{
    void WeatherMeasureProcess   (void * v_params);
    void DisplayWithTouchProcess (void * v_params);

    void MainCppHw (void)
    {
        static SystemTimeHw systemTimeHw;
        SET_SYSTEM_TIME_INST(&systemTimeHw);

        static RtosHw rtosHw;
        SET_RTOS_INST(&rtosHw);

        FlashHw flashHw;

        Rtos::GetInstance ()->TaskCreate (WeatherMeasureProcess,
                                          "WeatherMeasureProcess",
                                          EIGHT_THOUSAND_BYTES,
                                          static_cast <uint32_t> (RtosHw::EThreadPriority::eAboveNormal),
                                          WeatherMeasureTaskHandle);

        Rtos::GetInstance ()->TaskCreate (DisplayWithTouchProcess,
                                          "DisplayWithTouchProcess",
                                          THIRTY_THOUSAND_BYTES,
                                          static_cast <uint32_t> (RtosHw::EThreadPriority::eNormal),
                                          DisplayWithTouchTaskHandle);
    }

    void WeatherMeasureProcess (void * v_params)
    {
        WiFiHw               wifiHw;
        HttpClientHw         httpClientHw;
        WeatherMeasureParser weatherMeasureParser;
        WeatherMeasureComm   weatherMeasureComm (httpClientHw, weatherMeasureParser);
        TimerHw::Config      timerWeatherMeasureConfig;
        timerWeatherMeasureConfig.eTimer         = Timer<TimerHw>::ETimer::e1;
        timerWeatherMeasureConfig.Divider        = SIXTEEN;
        timerWeatherMeasureConfig.InterruptInSec = TWENTY;

        TimerHw timerWeatherMeasureHw (timerWeatherMeasureConfig);

        while (true)
        {
            if (Rtos::GetInstance ()->TakeSemaphore ("TakeWeatherMeasureSemaphore") == true)
            {
                weatherMeasureComm.Process ();
            }
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "WeatherMeasureProcess() Deleted.");

    }

    void DisplayWithTouchProcess (void * v_params)
    {
        GpioHw gpioHw;
        DisplayHw::Config_t displayConfig;
        displayConfig.Dimension.Width   = Settings::GetInstance ().Lcd.Width;
        displayConfig.Dimension.Height  = Settings::GetInstance ().Lcd.Height;
        displayConfig.LinesPerTransfer  = Settings::GetInstance ().Lcd.LinesPerTransfer;
        DisplayHw displayHw (displayConfig, gpioHw);

        Touch<TouchHw>::Config touchConfig;
        touchConfig.Histeresis          = TWO;
        touchConfig.Time.PressedMax     = FOUR;    // InterruptInSeconds * PressedMax
        touchConfig.Time.ReleasedMax    = EIGHT;

        TouchHw::Coefficients touchCoefficient;
        touchCoefficient.Constant       = ONE_HUNDRED_TWENTY_EIGHT;
        touchCoefficient.Width          = TWO;
        touchCoefficient.Length         = 2.67;

        TimerHw::Config timerTouchConfig;
        timerTouchConfig.eTimer         = Timer<TimerHw>::ETimer::e0;
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
            //baseWindow.Process ();
            LOGD (MODULE, "Temperature: %d", Settings::GetInstance ().WeatherMeasureMsgType.Current.Temperature)
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "DisplayWithTouchProcess() Deleted.");
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
