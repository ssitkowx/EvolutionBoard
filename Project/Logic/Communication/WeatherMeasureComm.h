#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "WiFi.h"
#include <string>
#include "HttpClientHw.h"
#include "Communication.h"
#include "WeatherMeasureParser.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class WeatherMeasureComm : public Communication<WeatherMeasureComm>
{
    static constexpr char * MODULE = (char *)"WeatherMeasureComm";
    friend Communication<WeatherMeasureComm>;

    private:
        static constexpr uint16_t      recvDataMaxLen = EIGHT_HUNDRED;
        char                      *    body           = NULL;
        cJSON                     *    root           = NULL;
        HttpClient<HttpClientHw>  &    http;
        WeatherMeasureParser      &    weatherMeasureParser;

        void send     (void) {}
        void receive  (void);
        void clear    (cJSON * v_root, char * v_body);

    public:
        class Chunk
        {
            friend class WeatherMeasureComm;
            private:
                char * payload;
                Chunk  (const uint16_t v_len) { payload = new char [v_len]; }
                ~Chunk ()                     { delete [] payload;}
        };

        explicit WeatherMeasureComm (HttpClient<HttpClientHw> & v_http,
                                     WeatherMeasureParser     & v_weatherMeasureParser) : http                 (v_http),
                                                                                          weatherMeasureParser (v_weatherMeasureParser) { }
        ~WeatherMeasureComm () = default;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


