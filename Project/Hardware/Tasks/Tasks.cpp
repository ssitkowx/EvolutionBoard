///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Tasks.h"
#include "RtosHw.h"
#include "MainCppHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static constexpr char * MODULE = (char *)"Tasks";

TaskHandle_t BluetoothTaskHandle;
TaskHandle_t WeatherMeasureTaskHandle;
TaskHandle_t DisplayAndTouchTaskHandle;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Tasks final : public MainCppHw
{
    static constexpr char * MODULE = (char *)"Tasks";
    public:
        Tasks () { LOG (MODULE, "Init."); }
       ~Tasks () = default;

       bool IsThreadInProgress (void) { return true; }
};

static class Tasks tasks;

extern "C"
{
    void Process (void)
    {
        Rtos::GetInstance ()->TaskCreate (BluetoothProcess,
                                          "BluetoothProcess",
                                          THIRTY_THOUSAND_BYTES,
                                          static_cast <uint32_t> (RtosHw::EThreadPriority::eAboveNormal),
                                          BluetoothTaskHandle);

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
}
void BluetoothProcess (void * v_params)
{
    while (true)
    {
        Rtos::GetInstance ()->DelayInMs (TEN);
    }

    Rtos::GetInstance ()->TaskDelete ();
    LOGE              (MODULE, "BluetoothProcess() Deleted.");
}

void WeatherMeasureProcess (void * v_params)
{
    while (true)
    {
        if (Rtos::GetInstance ()->TakeSemaphore ("TakeWeatherMeasureSemaphore") == true)
        {
            //tasks.WeatherMeasureComm.Process ();
        }
    }

    Rtos::GetInstance ()->TaskDelete ();
    LOGE              (MODULE, "WeatherMeasureProcess() Deleted.");

}

void DisplayAndTouchProcess (void * v_params)
{
    while (true)
    {
        //tasks.Action.Process ();
        Rtos::GetInstance ()->DelayInMs (TEN);
    }

    Rtos::GetInstance ()->TaskDelete ();
    LOGE              (MODULE, "DisplayAndTouchProcess() Deleted.");
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
