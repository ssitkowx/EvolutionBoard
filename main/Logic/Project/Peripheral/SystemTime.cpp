///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Settings.h"
#include "LoggerHw.h"
#include "SystemTime.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

SystemTime *                          SystemTime::instance;
std::chrono::system_clock::time_point SystemTime::timePoint;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void SystemTime::SetInstance (SystemTime * v_instance) { instance = v_instance; }

SystemTime * SystemTime::GetInstance (void)
{
    time_t currentTime;
    time (&currentTime);
    timePoint = std::chrono::system_clock::from_time_t (currentTime);
    
    return instance;
}

std::time_t SystemTime::InSeconds (void) const
{
    return std::chrono::system_clock::to_time_t (timePoint);
}

int64_t SystemTime::InMiliseconds (void)
{
    auto duration = timePoint.time_since_epoch ();
    return std::chrono::duration_cast<std::chrono::milliseconds> (duration).count ();
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
