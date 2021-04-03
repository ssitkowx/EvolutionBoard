///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "WeatherMeasureFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::AnyNumber;

static std::string_view weatherMeasureResp = "{\"request\": {\
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
                                                           \"Mist\",\
                                                           \"Sun\"\
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

ACTION_TEMPLATE (SetCloudResponse, HAS_1_TEMPLATE_PARAMS (char, ARG_NUM), AND_2_VALUE_PARAMS (v_cloudResp, v_len))
{
    memcpy ((char *)std::get<ARG_NUM> (args), (char *)v_cloudResp, v_len);
}

TEST_F (WeatherMeasureFixture, DownloadAndParseWeatherData)
{
    LOGW        (MODULE      , "DownloadAndParseWeatherData");

    EXPECT_CALL (rtosHw      , DelayInMs           (_))                                                     .Times          (AnyNumber ());
    EXPECT_CALL (rtosHw      , TaskDelete          ())                                                      .Times          (THREE);
    EXPECT_CALL (rtosHw      , GetCurrentHeapSize  ())                                                      .Times          (AnyNumber ());
    EXPECT_CALL (rtosHw      , GetCurrentStackSize (_))                                                     .Times          (AnyNumber ());
    EXPECT_CALL (draftsmanHw , DrawText            (_, _))                                                  .Times          (AnyNumber ());
    EXPECT_CALL (draftsmanHw , sendLines           (_))                                                     .Times          (AnyNumber ());
    EXPECT_CALL (httpClientHw, Cleanup             ())                                                      .Times          (AnyNumber ());
    EXPECT_CALL (httpClientHw, GetStatusCode       ())                                                      .Times          (AnyNumber ());
    EXPECT_CALL (touchHw     , isTouched           ())                                                      .Times          (AnyNumber ());

    WiFiHw::Mode.StaConnected = true;
    WeatherMeasureComm.SetState (WeatherMeasureComm::EState::eReceive);

    EXPECT_CALL (rtosHw      , TakeSemaphore (static_cast<std::string_view>("TakeWeatherMeasureSemaphore"))).WillOnce       (Return    (true))
                                                                                                            .WillRepeatedly (Return    (false));
    EXPECT_CALL (httpClientHw, Init                ())                                                      .WillOnce       (Return    (true))
                                                                                                            .WillRepeatedly (Return    (false));
    EXPECT_CALL (httpClientHw, Open                (ZERO))                                                  .WillOnce       (Return    (ZERO))
                                                                                                            .WillRepeatedly (Return    (ZERO));
    EXPECT_CALL (httpClientHw, FetchHeaders        ())                                                      .WillOnce       (Return    (weatherMeasureResp.size ()))
                                                                                                            .WillRepeatedly (Return    (ZERO));
    EXPECT_CALL (httpClientHw, Read                (_, _))                                                  .WillOnce       (DoAll     (SetCloudResponse <ZERO> (weatherMeasureResp.data(), weatherMeasureResp.size ()), Return (weatherMeasureResp.size ())));

    ::testing::InSequence queue;

    EXPECT_CALL (*this, IsThreadInProgress         ())                                                      .Times          (TEN)
                                                                                                            .WillRepeatedly (Return    (true));                                                                                                                 
    EXPECT_CALL (*this, IsThreadInProgress         ())                                                      .WillRepeatedly (Return    (false));

    Process     ();

    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Request.Type                               .data (), "City"            );
    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Request.Query                              .data (), "Warsaw, Poland"  );
    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Request.Language                           .data (), "en"              );
    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Request.Unit                               .data (), "m"               );
    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Location.Name                              .data (), "Warsaw"          );
    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Location.Country                           .data (), "Poland"          );
    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Location.Region                            .data (), ""                );
    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Location.Lat                               .data (), "52.250"          );
    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Location.Lon                               .data (), "21.000"          );
    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Location.TimezonId                         .data (), "Europe/Warsaw"   );
    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Location.LocalTime                         .data (), "2020-10-31 18:55");
    EXPECT_EQ    (Settings::GetInstance ().WeatherMeasureMsgType.Location.LocalTimeEpoch                            , 1604170500);
    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Location.UtcOffset                         .data (), "1.0");

    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Current.ObservationTime                    .data (), "05:55 PM"        );
    EXPECT_EQ    (Settings::GetInstance ().WeatherMeasureMsgType.Current.Temperature                                , 7                 );
    EXPECT_EQ    (Settings::GetInstance ().WeatherMeasureMsgType.Current.WeatherCode                                , 143               );
    EXPECT_EQ    (Settings::GetInstance ().WeatherMeasureMsgType.Current.WindSpeed                                  , 6                 );
    EXPECT_EQ    (Settings::GetInstance ().WeatherMeasureMsgType.Current.WindDegree                                 , 270               );
    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Current.WindDir                            .data (), "W"               );
    EXPECT_EQ    (Settings::GetInstance ().WeatherMeasureMsgType.Current.Pressure                                   , 1025              );
    EXPECT_EQ    (Settings::GetInstance ().WeatherMeasureMsgType.Current.Precip                                     , 0.1               );
    EXPECT_EQ    (Settings::GetInstance ().WeatherMeasureMsgType.Current.Humidity                                   , 100               );
    EXPECT_EQ    (Settings::GetInstance ().WeatherMeasureMsgType.Current.CloudCover                                 , 75                );
    EXPECT_EQ    (Settings::GetInstance ().WeatherMeasureMsgType.Current.FeelsLike                                  , 6                 );
    EXPECT_EQ    (Settings::GetInstance ().WeatherMeasureMsgType.Current.UvIndex                                    , 3                 );
    EXPECT_EQ    (Settings::GetInstance ().WeatherMeasureMsgType.Current.Visibility                                 , 6                 );
    EXPECT_STREQ (Settings::GetInstance ().WeatherMeasureMsgType.Current.IsDay                              .data (), "yes"             );
}

TEST_F (WeatherMeasureFixture, DownloadAndRedrawActivityWeather)
{
    LOGW        (MODULE      , "DownloadAndRedrawActivityWeather");

    EXPECT_CALL (rtosHw      , DelayInMs           (_))                                                           .Times          (AnyNumber ());
    EXPECT_CALL (rtosHw      , TaskDelete          ())                                                            .Times          (THREE);
    EXPECT_CALL (rtosHw      , GetCurrentHeapSize  ())                                                            .Times          (AnyNumber ());
    EXPECT_CALL (rtosHw      , GetCurrentStackSize (_))                                                           .Times          (AnyNumber ());
    EXPECT_CALL (draftsmanHw , DrawText            (_, _))                                                        .Times          (AnyNumber ());
    EXPECT_CALL (draftsmanHw , sendLines           (_))                                                           .Times          (AnyNumber ());
    EXPECT_CALL (httpClientHw, Cleanup             ())                                                            .Times          (AnyNumber ());
    EXPECT_CALL (httpClientHw, GetStatusCode       ())                                                            .Times          (AnyNumber ());
    EXPECT_CALL (touchHw     , isTouched           ())                                                            .Times          (AnyNumber ());

    WiFiHw::Mode.StaConnected = true;
    WeatherMeasureComm.SetState (WeatherMeasureComm::EState::eReceive);
    EXPECT_CALL (rtosHw      , TakeSemaphore       (static_cast<std::string_view>("TakeWeatherMeasureSemaphore"))).WillOnce       (Return    (true))
                                                                                                                  .WillRepeatedly (Return    (false));
    EXPECT_CALL (httpClientHw, Init                ())                                                            .WillOnce       (Return    (true))
                                                                                                                  .WillRepeatedly (Return    (false));
    EXPECT_CALL (httpClientHw, Open                (ZERO))                                                        .WillOnce       (Return    (ZERO))
                                                                                                                  .WillRepeatedly (Return    (ZERO));
    EXPECT_CALL (httpClientHw, FetchHeaders        ())                                                            .WillOnce       (Return    (weatherMeasureResp.size ()))
                                                                                                                  .WillRepeatedly (Return    (ZERO));
    EXPECT_CALL (httpClientHw, Read                (_, _))                                                        .WillOnce       (DoAll     (SetCloudResponse <ZERO> (weatherMeasureResp.data(), weatherMeasureResp.size ()), Return (weatherMeasureResp.size ())));


    SystemEvents::GetInstance   ().CircBuf                                                                        .Push ((uint8_t)(EActionId::eBButtonUp));
    SystemEvents::GetInstance   ().CircBuf                                                                        .Push ((uint8_t)(EActionId::eWeatherUpdated));

    EXPECT_CALL (draftsmanHw, DrawText            (ActivityWeather::Spaces   , _))                                .Times (SIX);
    EXPECT_CALL (draftsmanHw, DrawText            ((std::string_view)"Warsaw", _))                                .Times (ONE);
    EXPECT_CALL (draftsmanHw, DrawText            ((std::string_view)"100"   , _))                                .Times (ONE);
    EXPECT_CALL (draftsmanHw, DrawText            ((std::string_view)"75"    , _))                                .Times (ONE);
    EXPECT_CALL (draftsmanHw, DrawText            ((std::string_view)"6"     , _))                                .Times (ONE);
    EXPECT_CALL (draftsmanHw, DrawText            ((std::string_view)"7"     , _))                                .Times (ONE);
    EXPECT_CALL (draftsmanHw, DrawText            ((std::string_view)"1025"  , _))                                .Times (ONE);

    ::testing::InSequence queue;
    EXPECT_CALL (*this, IsThreadInProgress        ())                                                             .Times          (TEN)
                                                                                                                  .WillRepeatedly (Return    (true));
    EXPECT_CALL (*this, IsThreadInProgress        ())                                                             .WillRepeatedly (Return    (false));
    
    Process     ();
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

