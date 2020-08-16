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
            const uint8_t  RectNumbers         = FIFTEEN;
        } Lcd;

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
