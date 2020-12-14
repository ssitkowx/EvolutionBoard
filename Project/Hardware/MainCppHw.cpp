///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "RtosHw.h"
#include <stdint.h>
#include "GpioHw.h"
#include "WiFiHw.h"
#include "ILI9341.h"
#include "FLashHw.h"
#include "TouchHw.h"
#include "Settings.h"
#include "LoggerHw.h"
#include "BitmapHw.h"
#include "DisplayHw.h"
#include "SystemTimeHw.h"
#include "HttpClientHw.h"
#include "NumericKeyboard.h"
#include "WeatherMeasureComm.h"
#include "PresentationActivity.h"
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
/*
        Rtos::GetInstance ()->TaskCreate (WeatherMeasureProcess,
                                          "WeatherMeasureProcess",
                                          EIGHT_THOUSAND_BYTES,
                                          static_cast <uint32_t> (RtosHw::EThreadPriority::eBelowHigh),
                                          WeatherMeasureTaskHandle);
*/
        Rtos::GetInstance ()->TaskCreate (DisplayAndTouchProcess,
                                          "DisplayAndTouchProcess",
                                          THIRTY_THOUSAND_BYTES,
                                          static_cast <uint32_t> (RtosHw::EThreadPriority::eNormal),
                                          DisplayAndTouchTaskHandle);

    }

    void BluetoothProcess (void * v_params)
    {
        while (true)
        {

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
        const TimerHw::Config timerWeatherMeasureConfig = { SIXTEEN,                      // Divider
                                                            TWENTY,                       // InterruptInSec
                                                            Timer<TimerHw>::ETimer::e1    // eTimer,
                                                          };

        TimerHw timerWeatherMeasureHw (timerWeatherMeasureConfig);

        while (true)
        {
            if (Rtos::GetInstance ()->TakeSemaphore ("TakeWeatherMeasureSemaphore") == true)
            {
                weatherMeasureComm.Process ();
                Rtos::GetInstance ()->DelayInMs (ONE_HUNDRED);
            }
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "WeatherMeasureProcess() Deleted.");

    }

    void DisplayAndTouchProcess (void * v_params)
    {
        GpioHw                               gpioHw;
        SpiLcdHw                             spiLcdHw (gpioHw);
        ILI9341                              ili9341  (spiLcdHw);

        const DisplayHw::Config_t            displayConfig          = { Settings::GetInstance ().Lcd.LinesPerTransfer,    // Dimension.Width,
                                                                        Settings::GetInstance ().Lcd.Width,               // Dimension.Height
                                                                        Settings::GetInstance ().Lcd.Height               // LinesPerTransfer
                                                                      };

        DisplayHw                            displayHw (displayConfig, ili9341);

        const Touch<TouchHw>::Config         touchConfig            = { TWO,                                              // Histeresis
                                                                        FOUR,                                             // Time.PressedMax, InterruptInSeconds * PressedMax
                                                                        EIGHT                                             // Time.ReleasedMax
                                                                      };

        const TouchHw::Coefficients          touchCoefficients      = { ONE_HUNDRED_TWENTY_EIGHT,                         // Constant
                                                                        TWO,                                              // Width
                                                                        2.68                                              // Length
                                                                      };

        const TimerHw::Config                timerTouchConfig       = { SIXTEEN,                                          // Divider
                                                                        0.01,                                             // InterruptInSec
                                                                        Timer<TimerHw>::ETimer::e0                        // eTimer
                                                                      };

        TimerHw                              timerHw (timerTouchConfig);
        SpiTouchHw                           spiTouchHw;
        TouchHw                              touchHw (touchCoefficients, touchConfig, spiTouchHw);

        const NumericKeyboard::Configuration keyboardConfig         = { FIVE,                                             // BitmapSpacing.X
                                                                        FIVE,                                             // BitmapSpacing.Y
                                                                        FORTY,                                            // KeyboardStart.X
                                                                        ONE_HUNDRED_FIFTY                                 // KeyboardStart.Y
                                                                      };

        NumericKeyboard                      numericKeyboard      (keyboardConfig, displayHw, touchHw);
        PresentationActivity                 presentationActivity (displayHw, numericKeyboard);

        while (true)
        {
            presentationActivity.Process ();
            Rtos::GetInstance ()->DelayInMs (ONE);
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "DisplayAndTouchProcess() Deleted.");
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
