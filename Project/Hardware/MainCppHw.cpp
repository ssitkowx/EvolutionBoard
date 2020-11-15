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

    void DisplayAndTouchProcess (void * v_params)
    {
        GpioHw   gpioHw;
        SpiLcdHw spiLcdHw (gpioHw);
        ILI9341  ili9341 (spiLcdHw);

        DisplayHw::Config_t displayConfig;
        displayConfig.Dimension.Width   = Settings::GetInstance ().Lcd.Width;
        displayConfig.Dimension.Height  = Settings::GetInstance ().Lcd.Height;
        displayConfig.LinesPerTransfer  = Settings::GetInstance ().Lcd.LinesPerTransfer;
        DisplayHw displayHw (displayConfig, ili9341);

        Touch<TouchHw>::Config touchConfig;
        touchConfig.Histeresis          = TWO;
        touchConfig.Time.PressedMax     = FOUR;    // InterruptInSeconds * PressedMax
        touchConfig.Time.ReleasedMax    = EIGHT;

        TouchHw::Coefficients touchCoefficients;
        touchCoefficients.Constant      = ONE_HUNDRED_TWENTY_EIGHT;
        touchCoefficients.Width         = TWO;
        touchCoefficients.Length        = 2.67;

        TimerHw::Config timerTouchConfig;
        timerTouchConfig.eTimer         = Timer<TimerHw>::ETimer::e0;
        timerTouchConfig.Divider        = SIXTEEN;
        timerTouchConfig.InterruptInSec = 0.02;

        TouchHw touchHw (timerTouchConfig, touchCoefficients, touchConfig);

        NumericKeyboard::Configuration keyboardConfig;
        keyboardConfig.KeyboardStart.X  = EIGHTY;
        keyboardConfig.KeyboardStart.Y  = FORTY;
        keyboardConfig.BitmapSpacing.X  = FIVE;
        keyboardConfig.BitmapSpacing.Y  = FIVE;

        NumericKeyboard numericKeyboard (keyboardConfig, displayHw, touchHw);
        //BaseWindow      baseWindow      (displayHw);

        //////////////////////// Touch ////////////////////

        while (true)
        {
            numericKeyboard.Process ();
            displayHw.Process ();
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "DisplayAndTouchProcess() Deleted.");
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
