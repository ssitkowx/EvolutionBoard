#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <array>
#include <vector>
#include <string>
#include <Utils.h>
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class WeatherMeasureMsgType_t final
{
    public:
        struct
	    {
            std::array <char, FIVE_BYTES>                           Type;
            std::array <char, TWENTY_BYTES>                         Query;
            std::array <char, FIVE_BYTES>                           Language;
            std::array <char, TWO_BYTES>                            Unit;
	    } Request;

	    struct
	    {
	        std::array <char, TEN_BYTES>                            Name = { "Unknown" };
	        std::array <char, TEN_BYTES>                            Country;
	        std::array <char, TEN_BYTES>                            Region;
	        std::array <char, TEN_BYTES>                            Lat;
	        std::array <char, TEN_BYTES>                            Lon;
	        std::array <char, TWENTY_BYTES>                         TimezonId;
	        std::array <char, TWENTY_BYTES>                         LocalTime;
		    uint32_t                                                LocalTimeEpoch;
		    std::array <char, FIVE_BYTES>                           UtcOffset;
	    } Location;

	    struct
	    {
	        std::array <char, TEN_BYTES>                            ObservationTime;
		    int16_t                                                 Temperature;
		    int16_t                                                 WeatherCode;
		    std::array <std::array <char, ONE_HUNDRED_BYTES>, FIVE> WeatherIcons;
		    std::array <std::array <char, TEN_BYTES>, FIVE>         WeatherDescriptions;
		    uint8_t                                                 WindSpeed;
		    uint16_t                                                WindDegree;
		    std::array <char, TWO_BYTES>                            WindDir;
		    uint16_t                                                Pressure;
		    int8_t                                                  Precip;
		    uint8_t                                                 Humidity;
		    uint8_t                                                 CloudCover;
		    uint8_t                                                 FeelsLike;
		    uint8_t                                                 UvIndex;
		    uint8_t                                                 Visibility;
		    std::array <char, FIVE_BYTES>                           IsDay;
	    } Current;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


