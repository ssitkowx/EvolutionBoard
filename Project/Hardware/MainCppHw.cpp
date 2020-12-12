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
#include "BaseWindow.h"
#include "SystemTimeHw.h"
#include "HttpClientHw.h"
#include "NumericKeyboard.h"
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
        const TimerHw::Config timerWeatherMeasureConfig = { SIXTEEN, TWENTY, Timer<TimerHw>::ETimer::e1};
                                                          /*
                                                              Divider,
                                                              InterruptInSec,
                                                              eTimer
                                                          */

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
        GpioHw   gpioHw;
        SpiLcdHw spiLcdHw (gpioHw);
        ILI9341  ili9341  (spiLcdHw);

        const DisplayHw::Config_t displayConfig = { Settings::GetInstance ().Lcd.LinesPerTransfer, Settings::GetInstance ().Lcd.Width, Settings::GetInstance ().Lcd.Height };
                                                  /*
                                                      Dimension.Width,
                                                      Dimension.Height,
                                                      LinesPerTransfer
                                                  */

        DisplayHw displayHw (displayConfig, ili9341);

        const Touch<TouchHw>::Config touchConfig = { TWO, FOUR, EIGHT};
                                                   /*
                                                       Histeresis,
                                                       Time.PressedMax, InterruptInSeconds * PressedMax,
                                                       Time.ReleasedMax
                                                   */

        const TouchHw::Coefficients touchCoefficients = { ONE_HUNDRED_TWENTY_EIGHT, TWO, 2.68 };
                                                        /*
                                                            Constant,
                                                            Width,
                                                            Length
                                                        */

        const TimerHw::Config timerTouchConfig = { SIXTEEN, 0.01, Timer<TimerHw>::ETimer::e0 };
                                                 /*
                                                    Divider,
                                                    InterruptInSec,
                                                    eTimer
                                                 */
        TimerHw timerHw (timerTouchConfig);

        SpiTouchHw spiTouchHw;
        TouchHw touchHw (touchCoefficients, touchConfig, spiTouchHw);

        const NumericKeyboard::Configuration keyboardConfig = { FIVE, FIVE, FORTY, ONE_HUNDRED_FIFTY };
                                                              /*
                                                                 BitmapSpacing.X,
                                                                 BitmapSpacing.Y,
                                                                 KeyboardStart.X,
                                                                 KeyboardStart.Y
                                                              */

        NumericKeyboard numericKeyboard (keyboardConfig, displayHw, touchHw);
        BaseWindow      baseWindow      (displayHw, numericKeyboard);

        while (true)
        {
            baseWindow.Process ();
            Rtos::GetInstance ()->DelayInMs (ONE);
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "DisplayAndTouchProcess() Deleted.");
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
