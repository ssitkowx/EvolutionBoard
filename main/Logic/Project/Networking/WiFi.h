/**
 * Project: Lorch - Presents MicroTIG data on Azure Cloud.
 *
 * \file WiFi.h
 * \brief General class for WiFi.
 * \author sylsit
 * \date 2020.01.23
 * \copyright 2018 Fideltronik R&D - all rights reserved.
 * \version File template version 12.2018
*/

#pragma once 

/******************************************************************************
                                 INCLUDES
******************************************************************************/

#include <vector>
#include <stdint.h>
#include "Settings.h"

/******************************************************************************
                            MACROS/DEFINITIONS
******************************************************************************/

#define SSID_LEN     THIRTY_TWO_BYTES
#define PASSWORD_LEN SIXTY_FOUR_BYTES
#define MAC_LEN      SIX_BYTES

/******************************************************************************
                                 VARIABLES
******************************************************************************/

class WiFi
{
    public:
        enum class EMode
        {
            eStation,
            eAp,
        };

        struct Modes
        {
            bool Started         = false;
            bool StaConnected    = false;
            bool SoftApConnected = false;
        };

        static Modes Mode;

        WiFi () = default;
        virtual ~WiFi () = default;

        virtual void Reconnect (void) = 0;
        static bool  IsOnline  (void) { return WiFi::Mode.StaConnected; }

    protected:
        enum class EEvents
        {
            eStart,
            eStop,
            eDisconnected,
            eConnected,
            eGotIp,
            eLostIp,
            eEnabled,
            eDisabled,
            eApStart,
            eApDisconnected,
            eApConnected,
            eApEnabled,
            eApDisabled
        };

        struct Config
        {
            struct NetworkParams
            {
                std::string Ipv4;
                std::string Mask;
                std::string Gateway;
                std::string Ipv6;
            } NetParams;
            
            struct EModes
            {
                uint8_t Ssid     [SSID_LEN];
                uint8_t Password [PASSWORD_LEN];
            } Station = {{0}, {0}}, SoftAp = {{0}, {0}};
        } settings;

        virtual void startStation (void) = 0;
        virtual void startSoftAp  (void) = 0;

        void         switchMode   (EMode v_eMode);
        static  void onEvent      (EEvents v_event);
};

/******************************************************************************
                                 FUNCTIONS
******************************************************************************/

/****************************** END OF FILE  *********************************/

