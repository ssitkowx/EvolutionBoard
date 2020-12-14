#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <string>
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class WeatherMeasureMsgType_t final    // todo convenient in use but uneffective dynamic std::vector and std::string
{
    public:
        struct
	    {
	        std::string Type;
		    std::string Query;
	        std::string Language;
		    std::string Unit;
	    } Request;

	    struct
	    {
		    std::string Name;
		    std::string Country;
		    std::string Region;
		    std::string Lat;
		    std::string Lon;
		    std::string TimezonId;
		    std::string LocalTime;
		    uint32_t    LocalTimeEpoch;
		    std::string UtcOffset;
	    } Location;

	    struct
	    {
		    std::string ObservationTime;
		    int16_t     Temperature;
		    int16_t     WeatherCode;
		    std::vector <std::string> WeatherIcons;
		    std::vector <std::string> WeatherDescriptions;
		    uint8_t     WindSpeed;
		    uint16_t    WindDegree;
		    std::string WindDir;
		    uint16_t    Pressure;
		    int8_t      Precip;
		    uint8_t     Humidity;
		    uint8_t     CloudCover;
		    uint8_t     FeelsLike;
		    uint8_t     UvIndex;
		    uint8_t     Visibility;
		    std::string IsDay;
	    } Current;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


