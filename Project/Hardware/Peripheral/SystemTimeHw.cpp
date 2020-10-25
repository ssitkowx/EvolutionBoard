///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include "Settings.h"
#include "esp_sntp.h"
#include "LoggerHw.h"
#include "SystemTimeHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void SystemTimeHw::init (void)
{
    LOG                   (MODULE, "Init.");
    sntp_setoperatingmode (SNTP_OPMODE_POLL);
    sntp_setservername    (ZERO, (char *)Settings::GetInstance ().Sntp.Endpoint.c_str ());
    sntp_init             ();
}

std::string SystemTimeHw::getCurrentStringTime (void)
{
    time_t      timeNow;
    struct tm   timeinfo;

    time        (&timeNow);
    localtime_r (&timeNow, &timeinfo);
    
    std::string timeNowStr;
    setenv      (Settings::GetInstance ().Sntp.TimeZone.first.c_str (), Settings::GetInstance ().Sntp.TimeZone.second.c_str (), ONE);
    tzset       ();
    localtime_r (&timeNow, &timeinfo);
    strftime    ((char *)timeNowStr.c_str (), sizeof(timeNowStr), "%c", &timeinfo);

    return timeNowStr;
}

void SystemTimeHw::Update (void)
{
    init ();

    bool      isTimeSynchronized = false;
    int       retry              = ZERO;
    const int retryMax           = TEN;

    while ((isTimeSynchronized == false) && (++retry < retryMax))
    {
        sntp_sync_status_t syncStatus = sntp_get_sync_status ();
        if (syncStatus == SNTP_SYNC_STATUS_RESET)
        {
            LOGW (MODULE, "Try synchronize time with SNTP server. Attempt: (%d/%d).", retry, retryMax);
            Rtos::GetInstance()->DelayInMs (TWO_THOUSAND);
        }
        else
        {
            isTimeSynchronized = true;
            LOGI (MODULE, "SNTP server time synchronization succeeded.");
        }
    }
}

std::string SystemTimeHw::ToStringUTC () const
{
    std::time_t now    = std::chrono::system_clock::to_time_t (timePoint);
    std::tm     now_tm = { };
    
    localtime_r (&now, &now_tm);
    std::string stringTime;

    const auto timeStrLen = strftime ((char *)stringTime.c_str (), stringTime.size (), "%FT%T%z", &now_tm);
    if ((timeStrLen > ZERO) && (timeStrLen < stringTime.size ()))
    {
        stringTime [timeStrLen]       = '0';
        stringTime [timeStrLen - TWO] = ':';
    }

    return stringTime;
}

std::string SystemTimeHw::ToString (const char * v_format) const
{
    if (v_format == nullptr || strlen (v_format) == ZERO) return ToStringUTC ();

    std::chrono::system_clock::time_point hourFiveMinutes;    // Corrects displayed time
    hourFiveMinutes = std::chrono::system_clock::from_time_t (THREE_THOUSAND_SIX_HUNDRED);

    std::time_t now    = std::chrono::system_clock::to_time_t (timePoint) + std::chrono::system_clock::to_time_t (hourFiveMinutes);
    std::tm     now_tm = { };
    localtime_r (&now, &now_tm);

    char stringTime [FIFTY] = { };
    strftime (stringTime, sizeof (stringTime), v_format, &now_tm);

    return stringTime;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
