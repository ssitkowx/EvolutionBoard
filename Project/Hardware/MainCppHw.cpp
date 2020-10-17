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
#include "SystemTimeHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static constexpr char * MODULE = (char *)"MainCppHw";

TaskHandle_t DisplayAndTouchTaskHandle;
TaskHandle_t NetworkConnectionTaskHandle;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

extern "C"
{
    void DisplayAndTouchProcess    (void * v_params);
    void InternetConnectionProcess (void * v_params);

    void MainCppHw (void)
    {
        FlashHw flashHw;

        static RtosHw rtosHw;
        SET_RTOS_INST(&rtosHw);

        static SystemTimeHw systemTimeHw;
        SET_SYSTEM_TIME_INST(&systemTimeHw);

        Rtos::GetInstance()->TaskCreate (DisplayAndTouchProcess,
                                         "DisplayAndTouch",
                                         THIRTY_THOUSAND_BYTES,
                                         static_cast <uint32_t> (RtosHw::EThreadPriority::eNormal),
                                         DisplayAndTouchTaskHandle);
/*
        Rtos::GetInstance()->TaskCreate (&InternetConnectionProcess,
                                         "InternetConnection",
                                         FIVE_THOUSAND_BYTES,
                                         static_cast <uint32_t> (RtosHw::EThreadPriority::eAboveNormal),
                                         NetworkConnectionTaskHandle);
*/
    }

    void DisplayAndTouchProcess (void * v_params)
    {
        GpioHw                 gpioHw;
        Display::Configuration displayConfig;
        displayConfig.Dimension.Width  = Settings::GetInstance ().Lcd.Width;
        displayConfig.Dimension.Height = Settings::GetInstance ().Lcd.Height;
        displayConfig.LinesPerTransfer = Settings::GetInstance ().Lcd.LinesPerTransfer;
        DisplayHw              displayHw (gpioHw, displayConfig);

        Touch::Configuration touchConfig;
        touchConfig.Histeresis         = TWO;
        touchConfig.Time.PressedMax    = FOUR;    // InterruptInSeconds * PressedMax
        touchConfig.Time.ReleasedMax   = EIGHT;

        TouchHw::Coefficients touchCoefficient;
        touchCoefficient.Constant      = ONE_HUNDRED_TWENTY_EIGHT;
        touchCoefficient.Width         = TWO;
        touchCoefficient.Length        = 2.67;

        NumericKeyboard::Configuration config;
        config.KeyboardStart.X         = EIGHTY;
        config.KeyboardStart.Y         = FIFTY;
        config.BitmapSpacing.X         = FIVE;
        config.BitmapSpacing.Y         = FIVE;

        NumericKeyboard numericKeyboard (config, displayHw);

        TimerHw::Configuration timerConfig;
        timerConfig.eTimer             = Timer::ETimer::e0;
        timerConfig.Divider            = SIXTEEN;
        timerConfig.InterruptInSec     = 0.02;

        TouchHw touchHw (timerConfig, touchCoefficient, touchConfig, displayHw);

        //////////////////////// Touch ////////////////////

        while (true)
        {
            bool state = touchHw.IsPressed ();
            Rectangle rect = { };

            //simulation because touch issue
            rect.Coordinate.X = 150;
            rect.Coordinate.Y = 100;
            state = true;
            //end

            if (state == true)
            {
                //LOGD (MODULE, "pressed");
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum0Down), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum1Down), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum2Down), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum3Down), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum4Down), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum5Down), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum6Down), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum7Down), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum8Down), rect);
            }
            else
            {
                //LOGD (MODULE, "pressed not");
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum0Up), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum1Up), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum2Up), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum3Up), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum4Up), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum5Up), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum6Up), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum7Up), rect);
                numericKeyboard.Redraw (static_cast <uint8_t> (BitmapHw::EId::eKeyNum8Up), rect);
            }
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "DisplayAndTouchProcess() Deleted.");
    }

    void InternetConnectionProcess (void * v_params)
    {
        WiFiHw wifiHw;

        while (true)
        {
            //LOGV (MODULE, "InternetConnectionProcess. Stack left: %u", Rtos::GetInstance ()->GetCurrentStackSize ("InternetConnectionProcess"));
        }

        /*

        while (true)
        {
            if (Rtos::GetInstance ()->TakeAzureDataUpdateSemaphore () == true)
            {
                internetConnection.Process ();
            }
        }
*/
        vTaskDelete (NULL);
        LOGE        (MODULE, "InternetConnectionProcess() Deleted./n");

    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
