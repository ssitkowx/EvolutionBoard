///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "SpiHw.h"
#include "RtosHw.h"
#include <stdint.h>
#include "GpioHw.h"
//#include "Logger.h"
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

extern "C"
{
    void DisplayAndTouchProcess    (void * v_params);
    void InternetConnectionProcess (void * v_params);

    void MainCppHw (void)
    {
        static LoggerHw loggerHw;
        SET_LOGGER_INST(&loggerHw);

        static RtosHw RtosHw;
        SET_RTOS_INST(&RtosHw);

        static SystemTimeHw systemTimeHw;
        SET_SYSTEM_TIME_INST(&systemTimeHw);

        ESP_ERROR_CHECK (Rtos::GetInstance()->TaskCreate (&DisplayAndTouchProcess,
                                                          "DisplayAndTouch",
                                                          Settings::GetInstance ().Stack.DisplayAndTouch,
                                                          (uint32_t)RtosHw::EThreadPriority::eNormal,
                                                          DisplayAndTouchTaskHandle));

        ESP_ERROR_CHECK (Rtos::GetInstance()->TaskCreate (&InternetConnectionProcess,
                                                          "InternetConnection",
                                                          Settings::GetInstance ().Stack.InterntConnection,
                                                          (uint32_t)RtosHw::EThreadPriority::eAboveNormal,
                                                          InternetConnectionTaskHandle));
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
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "DisplayAndTouchProcess() Deleted");
    }

    void InternetConnectionProcess (void * v_params)
    {
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

        vTaskDelete (NULL);
        LOGE        (MODULE, "InternetConnectionProcess() Deleted");
        */
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
