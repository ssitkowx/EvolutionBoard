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
            const std::string Endpoint = "http://api.weatherstack.com/current?access_key=a2c288ed3ab5e85b50bea826fc81eded&query=warsaw";
            struct
            {
                std::string Key   = "access_key";
                std::string Value = "a2c288ed3ab5e85b50bea826fc81eded";
            } Authorization;
        } WeatherMeasure;

        struct
        {
            const std::string                          Endpoint = "pool.ntp.org";
            const std::pair <std::string, std::string> TimeZone = { "TZ", "UTC/GMT" };
        } Sntp;

        struct
        {
            const uint16_t Width            = THREE_HUNDRED_TWENTY;
            const uint16_t Height           = TWO_HUNDRED_FORTY;
            const uint16_t LinesPerTransfer = SIXTEEN;
        } Lcd;

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
