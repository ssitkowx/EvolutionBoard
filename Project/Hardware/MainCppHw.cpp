///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "RtosHw.h"
#include <stdint.h>
#include "GpioHw.h"
#include "WiFiHw.h"
#include "Action.h"
#include "FLashHw.h"
#include "TouchHw.h"
#include "SpiLcdHw.h"
#include "Settings.h"
#include "LoggerHw.h"
#include "Resources.h"
#include "DraftsmanHw.h"
#include "SystemTimeHw.h"
#include "HttpClientHw.h"
#include "WeatherMeasureComm.h"
#include "WeatherMeasureParser.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static constexpr char * MODULE = (char *)"MainCppHw";

TaskHandle_t BluetoothTaskHandle;
TaskHandle_t WeatherMeasureTaskHandle;
TaskHandle_t DisplayAndTouchTaskHandle;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

extern "C"
{
    void BluetoothProcess       (void * v_params);
    void DisplayAndTouchProcess (void * v_params);
    void WeatherMeasureProcess  (void * v_params);

    void MainCppHw (void)
    {
        static SystemTimeHw systemTimeHw;
        SET_SYSTEM_TIME_INST(&systemTimeHw);

        static RtosHw rtosHw;
        SET_RTOS_INST(&rtosHw);

        FlashHw flashHw;

/*
        Rtos::GetInstance ()->TaskCreate (BluetoothProcess,
                                          "BluetoothProcess",
                                          THIRTY_THOUSAND_BYTES,
                                          static_cast <uint32_t> (RtosHw::EThreadPriority::eAboveNormal),
                                          BluetoothTaskHandle);
*/

        Rtos::GetInstance ()->TaskCreate (WeatherMeasureProcess,
                                          "WeatherMeasureProcess",
                                          EIGHT_THOUSAND_BYTES,
                                          static_cast <uint32_t> (RtosHw::EThreadPriority::eBelowHigh),
                                          WeatherMeasureTaskHandle);

        Rtos::GetInstance ()->TaskCreate (DisplayAndTouchProcess,
                                          "DisplayAndTouchProcess",
                                          EIGHT_THOUSAND_BYTES,
                                          static_cast <uint32_t> (RtosHw::EThreadPriority::eNormal),
                                          DisplayAndTouchTaskHandle);
    }

    void BluetoothProcess (void * v_params)
    {
        while (true)
        {
            Rtos::GetInstance ()->DelayInMs (TEN);
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "BluetoothProcess() Deleted.");
    }

    void WeatherMeasureProcess (void * v_params)
    {
        WiFiHw                wifiHw;
        HttpClientHw          httpClientHw;
        WeatherMeasureParser  weatherMeasureParser;
        WeatherMeasureComm    weatherMeasureComm (httpClientHw, weatherMeasureParser);
        const TimerHw::Config timerWeatherMeasureConfig = { .Divider        = SIXTEEN,
                                                            .InterruptInSec = TWENTY,
                                                            .eTimer         = Timer<TimerHw>::ETimer::e1
                                                          };

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

    void DisplayAndTouchProcess (void * v_params)
    {
        GpioHw                               gpioHw;
        SpiLcdHw                             spiLcdHw            (gpioHw);
        SpiTouchHw                           spiTouchHw;

        const DraftsmanHw::Config_t          draftsmanConfig   = { .LinesPerTransfer = Settings::GetInstance ().Lcd.LinesPerTransfer,
                                                                   .Dimension        = { Settings::GetInstance ().Lcd.Width,
                                                                                         Settings::GetInstance ().Lcd.Height
                                                                                       }
                                                                 };

        Font                                 font;
        Resources                            resources           (font);
        DraftsmanHw                          draftsmanHw         (draftsmanConfig, spiLcdHw, font);

        const Touch<TouchHw>::Config         touchConfig       = { .Histeresis       =   TWO,
                                                                   .Time             = { FOUR,               // PressedMax, InterruptInSeconds * PressedMax
                                                                                         EIGHT               // ReleasedMax
                                                                                       }
                                                                 };

        const TouchHw::Coefficients          touchCoefficients = { .Constant         = ONE_HUNDRED_TWENTY_EIGHT,
                                                                   .Width            = TWO,
                                                                   .Length           = 2.68
                                                                 };

        const TimerHw::Config                timerTouchConfig  = { .Divider          = SIXTEEN,
                                                                   .InterruptInSec   = 0.01,
                                                                   .eTimer           = Timer<TimerHw>::ETimer::e0
                                                                 };

        TimerHw                              timerTouchHw        (timerTouchConfig);
        TouchHw                              touchHw             (touchCoefficients, touchConfig, spiTouchHw);
        Action                               action              (touchHw, draftsmanHw, resources);

        while (true)
        {
            action.Process ();
            Rtos::GetInstance ()->DelayInMs (TEN);
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "DisplayAndTouchProcess() Deleted.");
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
