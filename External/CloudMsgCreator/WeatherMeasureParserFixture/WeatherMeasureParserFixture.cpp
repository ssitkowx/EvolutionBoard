///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "LoggerMock.h"
#include "WeatherMeasureParserFixture.h"

static const char * const weatherMeasureResp = "{\"request\": {\
                                                     \"type\": \"City\",\
                                                     \"query\" : \"Warsaw, Poland\",\
                                                     \"language\" : \"en\",\
                                                     \"unit\" : \"m\"\
                                                   },\
                                                 \"location\": {\
                                                     \"name\": \"Warsaw\",\
                                                     \"country\" : \"Poland\",\
                                                     \"region\" : \"\",\
                                                     \"lat\" : \"52.250\",\
                                                     \"lon\" : \"21.000\",\
                                                     \"timezone_id\" : \"Europe/Warsaw\",\
                                                     \"localtime\" : \"2020-10-31 18:55\",\
                                                     \"localtime_epoch\" : 1604170500,\
                                                     \"utc_offset\" : \"1.0\"\
                                                   },\
                                                   \"current\": {\
                                                       \"observation_time\": \"05:55 PM\",\
                                                       \"temperature\" : 7,\
                                                       \"weather_code\" : 143,\
                                                       \"weather_icons\" : [\
                                                       \"https://assets.weatherstack.com/images/wsymbols01_png_64/wsymbol_0006_mist.png\"\
                                                       ] ,\
                                                       \"weather_descriptions\" : [\
                                                           \"Mist\"\
                                                       ] ,\
                                                       \"wind_speed\" : 6,\
                                                       \"wind_degree\" : 270,\
                                                       \"wind_dir\" : \"W\",\
                                                       \"pressure\" : 1025,\
                                                       \"precip\" : 0.1,\
                                                       \"humidity\" : 100,\
                                                       \"cloudcover\" : 75,\
                                                       \"feelslike\" : 6,\
                                                       \"uv_index\" : 3,\
                                                       \"visibility\" : 6,\
                                                       \"is_day\" : \"yes\"\
                                                  }\}";

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void WeatherMeasureParserFixture::Parse (void)
{
    LOGI (MODULE, "Parse.");

    cJSON * root = cJSON_Parse (weatherMeasureResp);
    weatherMeasureParser.Parse (root);

    char * jsonMessage = cJSON_Print (root);
    LOGW         (MODULE, jsonMessage);
    free         (jsonMessage);
    cJSON_Delete (root);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////