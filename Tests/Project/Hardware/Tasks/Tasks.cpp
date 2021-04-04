///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Tasks.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void Tasks::Process (void)
{
    std::unique_ptr<std::thread> bluetoothThread       (new std::thread ([this] { BluetoothProcess       (NULL); }));
    std::unique_ptr<std::thread> watherMeasureThread   (new std::thread ([this] { WeatherMeasureProcess  (NULL); }));
    std::unique_ptr<std::thread> displayAndTouchThread (new std::thread ([this] { DisplayAndTouchProcess (NULL); }));

    bluetoothCommThread       = std::move (bluetoothThread);
    watherMeasureCommThread   = std::move (watherMeasureThread);
    displayAndTouchCommThread = std::move (displayAndTouchThread);

    bluetoothCommThread      ->join ();
    watherMeasureCommThread  ->join ();
    displayAndTouchCommThread->join ();
}

void Tasks::BluetoothProcess (void * v_params)
{
    while (IsThreadInProgress ())
    {
        Rtos::GetInstance ()->DelayInMs (TEN);
    }

    Rtos::GetInstance ()->TaskDelete ();
    LOGE              (MODULE, "BluetoothProcess() Deleted.");
}

void Tasks::WeatherMeasureProcess (void * v_params)
{
    while (IsThreadInProgress ())
    {
        if (Rtos::GetInstance ()->TakeSemaphore ("TakeWeatherMeasureSemaphore") == true)
        {
            WeatherMeasureComm.Process ();
        }
    }

    Rtos::GetInstance ()->TaskDelete ();
    LOGE              (MODULE, "WeatherMeasureProcess() Deleted.");

}

void Tasks::DisplayAndTouchProcess (void * v_params)
{
    while (IsThreadInProgress ())
    {
        Action.Process ();
        Rtos::GetInstance ()->DelayInMs (TEN);
    }

    Rtos::GetInstance ()->TaskDelete ();
    LOGE              (MODULE, "DisplayAndTouchProcess() Deleted.");
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
