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

class WeatherMeasureComm : public Communication<WeatherMeasureComm>
{
    static constexpr char * MODULE = (char *)"WeatherMeasureComm";
    friend Communication<WeatherMeasureComm>;

    private:
        static constexpr uint16_t recvDataMaxLen = EIGHT_HUNDRED;
        char                 *    body           = NULL;
        cJSON                *    root           = NULL;
        HttpClient           &    http;
        WeatherMeasureParser &    weatherMeasureParser;

        void send     (void) {}
        void receive  (void);
        void clear    (cJSON * v_root, char * v_body);

    public:
        explicit WeatherMeasureComm (HttpClient           & v_http,
                                     WeatherMeasureParser & v_weatherMeasureParser) : http                 (v_http),
                                                                                      weatherMeasureParser (v_weatherMeasureParser) { }
        ~WeatherMeasureComm () = default;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


