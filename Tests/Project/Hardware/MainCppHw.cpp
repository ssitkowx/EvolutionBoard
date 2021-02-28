///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <thread>
#include "Utils.h"
#include <stdint.h>
#include "Action.h"
#include "RtosHw.h"
#include "GpioHw.h"
#include "WiFiHw.h"
#include "TimerHw.h"
#include "FlashHw.h"
#include "TouchHw.h"
#include "SpiLcdHw.h"
#include "Settings.h"
#include "MainCppHw.h"
#include "Resources.h"
#include "LoggerHw.h"
#include "SpiTouchHw.h"
#include "DraftsmanHw.h"
#include "SystemTimeHw.h"
#include "HttpClientHw.h"
#include "WeatherMeasureComm.h"
#include "WeatherMeasureParser.h"
//
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

MainCppHw::MainCppHw ()
{
    static SystemTimeHw systemTimeHw;
    SET_SYSTEM_TIME_INST (&systemTimeHw);

    static RtosHw rtosHw;
    SET_RTOS_INST (&rtosHw);

    FlashHw flashHw;
}

void MainCppHw::BluetoothProcess (void)
{
     while (isThreadInProgress == true)
     {
         std::this_thread::sleep_for (std::chrono::milliseconds (TEN));
     }

     LOGE (MODULE, "bluetoothProcess() Deleted.");
}

void MainCppHw::WeatherMeasureProcess (void)
{
    WiFiHw                wifiHw;
    HttpClientHw          httpClientHw;
    WeatherMeasureParser  weatherMeasureParser;
    WeatherMeasureComm    weatherMeasureComm (httpClientHw, weatherMeasureParser);
    const TimerHw::Config timerWeatherMeasureConfig = { .Divider = SIXTEEN,
                                                        .InterruptInSec = TWENTY,
                                                        .eTimer = Timer<TimerHw>::ETimer::e1
                                                      };

    TimerHw timerWeatherMeasureHw (timerWeatherMeasureConfig);

    while (isThreadInProgress == true)
    {
        if (Rtos::GetInstance ()->TakeSemaphore ("TakeWeatherMeasureSemaphore") == true)
        {
            weatherMeasureComm.Process ();
        }
    }

    LOGE (MODULE, "weatherMeasureProcess() Deleted.");
}

void MainCppHw::DisplayAndTouchProcess ()
{
    GpioHw                       gpioHw;
    SpiLcdHw                     spiLcdHw (gpioHw);
    SpiTouchHw                   spiTouchHw;

    const DraftsmanHw::Config_t  draftsmanConfig = { .LinesPerTransfer = Settings::GetInstance ().Lcd.LinesPerTransfer,
                                                     .Dimension        = { Settings::GetInstance ().Lcd.Width,
                                                                           Settings::GetInstance ().Lcd.Height
                                                                         }
                                                   };

    Font                         font;
    Resources                    resources (font);
    DraftsmanHw                  draftsmanHw (draftsmanConfig);

    const Touch<TouchHw>::Config touchConfig = { .Histeresis = TWO,
                                                 .Time       = { FOUR,               // PressedMax, InterruptInSeconds * PressedMax
                                                                 EIGHT               // ReleasedMax
                                                 }
                                               };


    const TimerHw::Config        timerTouchConfig = { .Divider = SIXTEEN,
                                                      .InterruptInSec = 0.01,
                                                      .eTimer = Timer<TimerHw>::ETimer::e0
                                                    };

    TimerHw                      timerTouchHw (timerTouchConfig);
    TouchHw                      touchHw (touchConfig);
    Action                       action (touchHw, draftsmanHw, resources);

    while (isThreadInProgress == true)
    {
        action.Process ();
        std::this_thread::sleep_for (std::chrono::milliseconds (ONE));
    }

    LOGE (MODULE, "displayAndTouchProcess() Deleted.");
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
