///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <memory>
#include "Utils.h"
#include "Settings.h"
#include "WeatherMeasureParser.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void WeatherMeasureParser::Request (cJSON * v_root)
{
	cJSON * type = cJSON_GetObjectItem (v_root, "type");
	isNodeJsonEmpty ("Request", "type", type);
	memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Request.Type.data(), type->valuestring, strlen (type->valuestring));

	cJSON * query = cJSON_GetObjectItem (v_root, "query");
	isNodeJsonEmpty ("Request", "query", query);
	memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Request.Query.data(), query->valuestring, strlen (query->valuestring));

	cJSON * language = cJSON_GetObjectItem (v_root, "language");
	isNodeJsonEmpty ("Request", "language", language);
	memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Request.Language.data(), language->valuestring, strlen (language->valuestring));

	cJSON * unit = cJSON_GetObjectItem (v_root, "unit");
	isNodeJsonEmpty ("Request", "unit", unit);
	memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Request.Unit.data(), unit->valuestring, strlen (unit->valuestring));
}

void WeatherMeasureParser::Location (cJSON * v_root)
{
	cJSON * name = cJSON_GetObjectItem (v_root, "name");
    isNodeJsonEmpty ("Location", "name", name);
    memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Location.Name.data(), name->valuestring, strlen (name->valuestring));

	cJSON * country = cJSON_GetObjectItem (v_root, "country");
	isNodeJsonEmpty ("Location", "country", country);
	memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Location.Country.data (), country->valuestring, strlen (country->valuestring));

	cJSON * region = cJSON_GetObjectItem (v_root, "region");
	isNodeJsonEmpty ("Location", "region", region);
	memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Location.Region.data (), region->valuestring, strlen (region->valuestring));

	cJSON * lat = cJSON_GetObjectItem (v_root, "lat");
	isNodeJsonEmpty ("Location", "lat", lat);
	memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Location.Lat.data (), lat->valuestring, strlen (lat->valuestring));

	cJSON * lon = cJSON_GetObjectItem (v_root, "lon");
	isNodeJsonEmpty ("Location", "lon", lon);
	memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Location.Lon.data (), lon->valuestring, strlen (lon->valuestring));

	cJSON * timezoneId = cJSON_GetObjectItem (v_root, "timezone_id");
	isNodeJsonEmpty ("Location", "timezone_id", timezoneId);
	memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Location.TimezonId.data (), timezoneId->valuestring, strlen (timezoneId->valuestring));

	cJSON * localTime = cJSON_GetObjectItem (v_root, "localtime");
	isNodeJsonEmpty ("Location", "localtime", localTime);
	memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Location.LocalTime.data (), localTime->valuestring, strlen (localTime->valuestring));

	cJSON * localTimeEpoch = cJSON_GetObjectItem (v_root, "localtime_epoch");
	isNodeJsonEmpty ("Location", "localtime_epoch", localTimeEpoch);
	Settings::GetInstance ().WeatherMeasureMsgType.Location.LocalTimeEpoch = localTimeEpoch->valueint;

	cJSON * utcOffset = cJSON_GetObjectItem (v_root, "utc_offset");
	isNodeJsonEmpty ("Location", "utc_offset", utcOffset);
	memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Location.UtcOffset.data (), utcOffset->valuestring, strlen (utcOffset->valuestring));
}

void WeatherMeasureParser::Current (cJSON * v_root)
{
	cJSON * observationTime = cJSON_GetObjectItem (v_root, "observation_time");
	isNodeJsonEmpty ("Current", "observation_time", observationTime);
	memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Current.ObservationTime.data (), observationTime->valuestring, strlen (observationTime->valuestring));

	cJSON * temperature = cJSON_GetObjectItem (v_root, "temperature");
	isNodeJsonEmpty ("Current", "temperature", temperature);
	Settings::GetInstance ().WeatherMeasureMsgType.Current.Temperature = temperature->valueint;

	cJSON * weatherCode = cJSON_GetObjectItem (v_root, "weather_code");
	isNodeJsonEmpty ("Current", "weather_code", weatherCode);
	Settings::GetInstance ().WeatherMeasureMsgType.Current.WeatherCode = weatherCode->valueint;

	cJSON * weatherIcons = cJSON_GetObjectItem (v_root, "weather_icons");
	for (uint8_t valueNum = ZERO; valueNum < cJSON_GetArraySize (weatherIcons); valueNum++)
	{
		cJSON * subitem = cJSON_GetArrayItem  (weatherIcons, valueNum);
		memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Current.WeatherIcons [valueNum].data (), subitem->valuestring, strlen (subitem->valuestring));
	}

	cJSON * weatherDescription = cJSON_GetObjectItem (v_root, "weather_descriptions");
	for (uint8_t valueNum = ZERO; valueNum < cJSON_GetArraySize (weatherDescription); valueNum++)
	{
		cJSON * subitem = cJSON_GetArrayItem (weatherDescription, valueNum);
		memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Current.WeatherDescriptions [valueNum].data (), subitem->valuestring, strlen (subitem->valuestring));
	}

	cJSON * windSpeed = cJSON_GetObjectItem (v_root, "wind_speed");
	isNodeJsonEmpty ("Current", "wind_speed", windSpeed);
	Settings::GetInstance ().WeatherMeasureMsgType.Current.WindSpeed = windSpeed->valueint;

	cJSON * windDegree = cJSON_GetObjectItem (v_root, "wind_degree");
	isNodeJsonEmpty ("Current", "wind_degree", windDegree);
	Settings::GetInstance ().WeatherMeasureMsgType.Current.WindDegree = windDegree->valueint;

	cJSON * windDir = cJSON_GetObjectItem (v_root, "wind_dir");
	isNodeJsonEmpty ("Current", "wind_dir", windDir);
	memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Current.WindDir.data (), windDir->valuestring, strlen (windDir->valuestring));

	cJSON * pressure = cJSON_GetObjectItem (v_root, "pressure");
	isNodeJsonEmpty ("Current", "pressure", pressure);
	Settings::GetInstance ().WeatherMeasureMsgType.Current.Pressure = pressure->valueint;

	cJSON * precip = cJSON_GetObjectItem (v_root, "precip");
	isNodeJsonEmpty ("Current", "precip", precip);
	Settings::GetInstance ().WeatherMeasureMsgType.Current.Precip = precip->valueint;

	cJSON * humidity = cJSON_GetObjectItem (v_root, "humidity");
	isNodeJsonEmpty ("Current", "humidity", humidity);
	Settings::GetInstance ().WeatherMeasureMsgType.Current.Humidity = humidity->valueint;

	cJSON * cloudcover = cJSON_GetObjectItem (v_root, "cloudcover");
	isNodeJsonEmpty ("Current", "cloudcover", cloudcover);
	Settings::GetInstance ().WeatherMeasureMsgType.Current.CloudCover = cloudcover->valueint;

	cJSON * feelslike = cJSON_GetObjectItem (v_root, "feelslike");
	isNodeJsonEmpty ("Current", "feelslike", feelslike);
	Settings::GetInstance ().WeatherMeasureMsgType.Current.FeelsLike = feelslike->valueint;

	cJSON * uvIndex = cJSON_GetObjectItem (v_root, "uv_index");
	isNodeJsonEmpty ("Current", "uv_index", uvIndex);
	Settings::GetInstance ().WeatherMeasureMsgType.Current.UvIndex = uvIndex->valueint;

	cJSON * visibility = cJSON_GetObjectItem (v_root, "visibility");
	isNodeJsonEmpty ("Current", "visibility", visibility);
	Settings::GetInstance ().WeatherMeasureMsgType.Current.Visibility = visibility->valueint;

	cJSON * isDay = cJSON_GetObjectItem (v_root, "is_day");
	isNodeJsonEmpty ("Current", "is_day", isDay);
	memcpy (Settings::GetInstance ().WeatherMeasureMsgType.Current.IsDay.data (), isDay->valuestring, strlen (isDay->valuestring));
}

void WeatherMeasureParser::Parse (cJSON * v_root)
{
	isNodeJsonEmpty ("Parse", "root", v_root);

	cJSON * request = cJSON_GetObjectItem (v_root, "request");
	isNodeJsonEmpty ("Parse", "request", request);
	Request         (request);

	cJSON * location = cJSON_GetObjectItem (v_root, "location");
	isNodeJsonEmpty ("Parse", "location", location);
	Location        (location);

	cJSON * current = cJSON_GetObjectItem (v_root, "current");
	isNodeJsonEmpty ("Parse", "current", current);
	Current         (current);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
