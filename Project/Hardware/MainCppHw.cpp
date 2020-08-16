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
        displayConfig.Length              = Settings::GetInstance ().Lcd.Length;
        displayConfig.Width               = Settings::GetInstance ().Lcd.Width;
        displayConfig.MaxLinesPerTransfer = Settings::GetInstance ().Lcd.MaxLinesPerTransfer;
        displayConfig.RectNumbers         = Settings::GetInstance ().Lcd.RectNumbers;
        DisplayHw              displayHw (gpioHw, displayConfig);

        Touch::Configuration touchConfig;
        touchConfig.Histeresis       = TWO;
        touchConfig.Time.PressedMax  = FOUR;    // InterruptInSeconds * PressedMax
        touchConfig.Time.ReleasedMax = EIGHT;

        TouchHw::Coefficients touchCoefficient;
        touchCoefficient.Constant = ONE_HUNDRED_TWENTY_EIGHT;
        touchCoefficient.Width    = TWO;
        touchCoefficient.Length   = 2.67;

        TimerHw::Configuration timerConfig;
        timerConfig.eTimer         = Timer::ETimer::e0;
        timerConfig.Divider        = SIXTEEN;
        timerConfig.InterruptInSec = 0.02;

        TouchHw touchHw (timerConfig, touchCoefficient, touchConfig, displayHw);

        //////////////////////// Touch ////////////////////

        while (true)
        {
            touchHw.Process ();
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
        HttpClientHw      httpClientHw;
        MicorTigAzureComm micorTigAzureComm (httpClientHw);

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
