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
    public:
        static constexpr char *      MODULE = (char *)"MainCppHw";
        std::shared_ptr<std::thread> BluetoothCommThread;
        std::shared_ptr<std::thread> WatherMeasureCommThread;
        std::shared_ptr<std::thread> DisplayAndTouchCommThread;

        MainCppHw () { Init (); }
        ~MainCppHw () = default;

        void Process (void)
        {
            std::shared_ptr<std::thread> bluetoothThread       (new std::thread (BluetoothProcess      , this));
            std::shared_ptr<std::thread> watherMeasureThread   (new std::thread (WeatherMeasureProcess , this));
            std::shared_ptr<std::thread> displayAndTouchThread (new std::thread (DisplayAndTouchProcess, this));

            BluetoothCommThread       = std::move (bluetoothThread);
            WatherMeasureCommThread   = std::move (watherMeasureThread);
            DisplayAndTouchCommThread = std::move (displayAndTouchThread);

            BluetoothCommThread      ->join ();
            WatherMeasureCommThread  ->join ();
            DisplayAndTouchCommThread->join ();
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
