///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "SpiHw.h"
#include "RtosHw.h"
#include <stdint.h>
#include "GpioHw.h"
#include "WiFiHw.h"
#include "FLashHw.h"
#include "Settings.h"
#include "LoggerHw.h"
#include "DisplayHw.h"
#include "SystemTimeHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static constexpr char * MODULE = (char *)"MainCppHw";

TaskHandle_t DisplayAndTouchTaskHandle;
TaskHandle_t InternetConnectionTaskHandle;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#include "nvs_flash.h"
extern "C"
{
    void DisplayAndTouchProcess    (void * v_params);
    void InternetConnectionProcess (void * v_params);

    void MainCppHw (void)
    {
        static LoggerHw loggerHw;
        SET_LOGGER_INST(&loggerHw);

        static RtosHw rtosHw;
        SET_RTOS_INST(&rtosHw);

        static SystemTimeHw systemTimeHw;
        SET_SYSTEM_TIME_INST(&systemTimeHw);

        FlashHw flashHw;

        Rtos::GetInstance()->TaskCreate (DisplayAndTouchProcess,
                                         "DisplayAndTouch",
                                         Settings::GetInstance ().StackDepth.DisplayAndTouch,
                                         static_cast <uint32_t> (RtosHw::EThreadPriority::eNormal),
                                         DisplayAndTouchTaskHandle);

        Rtos::GetInstance()->TaskCreate (&InternetConnectionProcess,
                                         "InternetConnection",
                                         Settings::GetInstance ().StackDepth.InterntConnection,
                                         static_cast <uint32_t> (RtosHw::EThreadPriority::eAboveNormal),
                                         InternetConnectionTaskHandle);
    }

    void DisplayAndTouchProcess (void * v_params)
    {
        GpioHw    gpioHw;
        SpiHw     spiHw;
        DisplayHw display (gpioHw, spiHw);

        uint16_t xPos   = 50;
        uint16_t yPos   = 50;
        uint16_t width  = 100;
        uint16_t length = 100;

        display.DrawRect (xPos        , yPos, width, length, Display::EColors::ePurple);
        display.DrawRect (xPos + width, yPos, width, length, Display::EColors::eMagneta);

        while (true)
        {
            //displayAndTouch.Process ();

            LOGI (MODULE, "DisplayAndTouchProcess. Stack left: %u", Rtos::GetInstance ()->GetCurrentStackSize ("DisplayAndTouch"));
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "DisplayAndTouchProcess() Deleted.");
    }

    void InternetConnectionProcess (void * v_params)
    {
        WiFiHw wifiHw;

        while (true)
        {
            LOGV (MODULE, "InternetConnectionProcess. Stack left: %u", Rtos::GetInstance ()->GetCurrentStackSize ("InternetConnectionProcess"));
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
