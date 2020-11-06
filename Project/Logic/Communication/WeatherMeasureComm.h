#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "WiFi.h"
#include <string>
#include "HttpClient.h"
#include "Communication.h"
#include "WeatherMeasureParser.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class WeatherMeasureComm : public Communication
{
    static constexpr char * MODULE = (char *)"WeatherMeasureComm";

    private:
        static constexpr uint16_t recvDataMaxLen = EIGHT_HUNDRED;
        char                 *    body           = NULL;
        cJSON                *    root           = NULL;
        HttpClient           &    http;
        WeatherMeasureParser &    weatherMeasureParser;

        class Chunk
        {
            friend class WeatherMeasureComm;
            private:
                char * payload;
                Chunk  (const uint16_t v_len) { payload = new char [v_len]; }
                ~Chunk ()                     { free (payload);}
        };

        void send     (void) override {}
        void receive  (void) override;

        bool isOnline (void);
        void clear    (cJSON * v_root, char * v_body);

    public:
        WeatherMeasureComm (HttpClient & v_http, WeatherMeasureParser & v_weatherMeasureParser) : http (v_http), weatherMeasureParser (v_weatherMeasureParser) { }
        ~WeatherMeasureComm () = default;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


