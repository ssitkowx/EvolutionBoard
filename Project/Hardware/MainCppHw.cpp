///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Tasks.h"
#include "RtosHw.h"
#include "MainCppHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TaskHandle_t BluetoothTaskHandle;
TaskHandle_t WeatherMeasureTaskHandle;
TaskHandle_t DisplayAndTouchTaskHandle;

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class MainCppHw final
{
    static constexpr char * MODULE = (char *)"MainCppHw";

    public:
        MainCppHw () { Init (); }
        ~MainCppHw () = default;

        void Process (void)
        {

    /*
            Rtos::GetInstance ()->TaskCreate (BluetoothProcess,
                                              "BluetoothProcess",
                                              THIRTY_THOUSAND_BYTES,
                                              static_cast <uint32_t> (RtosHw::EThreadPriority::eAboveNormal),
                                              BluetoothTaskHandle);
    */

            Rtos::GetInstance ()->TaskCreate (WeatherMeasureProcess,
                                              "WeatherMeasureProcess",
                                              EIGHT_THOUSAND_BYTES,
                                              static_cast <uint32_t> (RtosHw::EThreadPriority::eBelowHigh),
                                              WeatherMeasureTaskHandle);

            Rtos::GetInstance ()->TaskCreate (DisplayAndTouchProcess,
                                              "DisplayAndTouchProcess",
                                              EIGHT_THOUSAND_BYTES,
                                              static_cast <uint32_t> (RtosHw::EThreadPriority::eNormal),
                                              DisplayAndTouchTaskHandle);
        }
};


extern "C"
{
    void Process (void)
    {
        MainCppHw mainCppHw;
        mainCppHw.Process ();
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
