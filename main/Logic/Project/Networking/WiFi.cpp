/**
 * Project: Lorch - Presents MicroTIG data on Azure Cloud.
 *
 * \file WiFi.cpp
 * \brief
 * \author sylsit
 * \date 2020.01.23
 * \copyright 2018 Fideltronik R&D - all rights reserved.
 * \version File template version 12.2018
*/

/******************************************************************************
                                 INCLUDES
******************************************************************************/

#include "WiFi.h"
#include "LoggerHw.h"

/******************************************************************************
                            MACROS/DEFINITIONS
******************************************************************************/

/******************************************************************************
                                 VARIABLES
******************************************************************************/

WiFi::Modes WiFi::Mode;

/******************************************************************************
                                 FUNCTIONS
******************************************************************************/

/**
 * \brief Switch mode to station or soft ap.
 */

void WiFi::switchMode (EMode v_eMode)
{
    switch (v_eMode)
    {
        case EMode::eStation:
        {
            startStation ();
            break;
        }
        case EMode::eAp:
        {
            startSoftAp ();
            break;
        }
        default:
        {
            break;
        }
    }
}

/**
 * \brief Event handler.
 */

void WiFi::onEvent (EEvents v_event)
{
    if (v_event == EEvents::eStart)
    {
        Mode.Started      = true;
        Mode.StaConnected = false;
    }
    if (v_event == EEvents::eStop)
    {
        Mode.Started      = false;
        Mode.StaConnected = false;
    }
    if (v_event == EEvents::eDisconnected || v_event == EEvents::eDisabled || v_event == EEvents::eLostIp)
    {
        Mode.StaConnected = false;
    }
    else if (v_event == EEvents::eConnected) { }
    if (v_event == EEvents::eGotIp)
    {
        Mode.StaConnected = true;
    }
    else if (v_event == EEvents::eApConnected)
    {
        Mode.SoftApConnected = true;
    }
    else if (v_event == EEvents::eApDisconnected)
    {
        Mode.SoftApConnected = false;
    }
    else if (v_event == EEvents::eApEnabled)
    {
        /*
        webServer.Start();
        captivePortal.reset(new CaptiveDNS());
        captivePortal.get()->Start();
        */
    }
    else if (v_event == EEvents::eApDisabled)
    {
        /*
        captivePortal = nullptr;
        webServer.Stop();
        */
    }
}

/****************************** END OF FILE  *********************************/
