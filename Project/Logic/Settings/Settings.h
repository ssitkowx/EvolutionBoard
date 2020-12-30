#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include <stdint.h>
#include <string.h>
#include "WeatherMeasureMsgType.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Settings
{
    public:
        struct
        {
            std::string_view Endpoint = "http://api.weatherstack.com/current?access_key=a2c288ed3ab5e85b50bea826fc81eded&query=warsaw";
            struct
            {
                std::string_view Key   = "access_key";
                std::string_view Value = "a2c288ed3ab5e85b50bea826fc81eded";
            } Authorization;
        } WeatherMeasure;

        struct
        {
            std::string_view                          Endpoint = "pool.ntp.org";
            std::pair <std::string, std::string_view> TimeZone = { "TZ", "UTC/GMT" };
        } Sntp;

        struct
        {
            const uint16_t Width            = TWO_HUNDRED_FORTY;
            const uint16_t Height           = THREE_HUNDRED_TWENTY;
            const uint16_t LinesPerTransfer = SIXTEEN;
        } Lcd;

        struct
        {
            struct
            {
                std::string_view Ssid     = "UPC9763179";
                std::string_view Password = "Fbs3xjxvbmm3";
            } Station;

            struct
            {
                std::string_view Ssid;
                std::string_view Password;
            } SoftAp;
        } WiFi;

        WeatherMeasureMsgType_t WeatherMeasureMsgType;

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
