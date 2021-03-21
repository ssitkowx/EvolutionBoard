#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <thread>
#include "Tasks.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class MainCppHw final
{
    private:
        std::shared_ptr<std::thread> bluetoothCommThread;
        std::shared_ptr<std::thread> watherMeasureCommThread;
        std::shared_ptr<std::thread> displayAndTouchCommThread;

    public:
        MainCppHw () { Init (); }
        ~MainCppHw () = default;

        void Process (void)
        {
            std::shared_ptr<std::thread> bluetoothThread       (new std::thread (BluetoothProcess      , this));
            std::shared_ptr<std::thread> watherMeasureThread   (new std::thread (WeatherMeasureProcess , this));
            std::shared_ptr<std::thread> displayAndTouchThread (new std::thread (DisplayAndTouchProcess, this));

            bluetoothCommThread       = std::move (bluetoothThread);
            watherMeasureCommThread   = std::move (watherMeasureThread);
            displayAndTouchCommThread = std::move (displayAndTouchThread);

            bluetoothCommThread      ->join ();
            watherMeasureCommThread  ->join ();
            displayAndTouchCommThread->join ();
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
