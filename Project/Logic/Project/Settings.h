#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include <stdint.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Settings
{
    public:
        struct
        {
            const uint16_t Length              = TWO_HUNDRED_FORTY;
            const uint16_t Width               = THREE_HUNDRED_TWENTY;
            const uint16_t MaxLinesPerTransfer = TWELVE;
            const uint8_t  RectsNumber         = FIFTEEN;
        } Lcd;

        struct
        {
            const uint32_t DisplayAndTouch   = 30000;
            const uint32_t InterntConnection = 5000;
        } StackDepth;

        struct
        {
            const std::string                          Endpoint = "pool.ntp.org";
            const std::pair <std::string, std::string> TimeZone = { "TZ", "UTC/GMT" };
        } Sntp;

        struct
        {
            struct
            {
                const std::string Ssid     = "UPC9763179";
                const std::string Password = "Fbs3xjxvbmm3";
            } Station;

            struct
            {
                const std::string Ssid;
                const std::string Password;
            } SoftAp;
        } WiFi;
/*
        struct
        {
            const uint32_t TimerDivider;
            const uint32_t TimerInteruptInSeconds;
        } Timer;
*/
        Settings () = default;

        static Settings & GetInstance (void)
        {
            static Settings instance;
            return instance;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
