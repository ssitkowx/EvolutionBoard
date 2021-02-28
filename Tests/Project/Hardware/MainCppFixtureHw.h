#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <thread>
#include "MainCppHw.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class MainCppFixtureHw : public MainCppHw, public ::testing::Test
{
    public:
        static constexpr char * MODULE = (char *)"MainCppFixtureHw";

        MainCppFixtureHw () = default;
        ~MainCppFixtureHw () = default;

        std::shared_ptr<std::thread> BluetoothCommThread;
        std::shared_ptr<std::thread> WatherMeasureCommThread;
        std::shared_ptr<std::thread> DisplayAndTouchCommThread;

        void Process (void)
        {
            std::shared_ptr<std::thread> bluetoothThread       (new std::thread (&MainCppHw::BluetoothProcess      , this));
            std::shared_ptr<std::thread> watherMeasureThread   (new std::thread (&MainCppHw::WeatherMeasureProcess , this));
            std::shared_ptr<std::thread> displayAndTouchThread (new std::thread (&MainCppHw::DisplayAndTouchProcess, this));

            BluetoothCommThread       = std::move (bluetoothThread);
            WatherMeasureCommThread   = std::move (watherMeasureThread);
            DisplayAndTouchCommThread = std::move (displayAndTouchThread);

            BluetoothCommThread      ->join ();
            WatherMeasureCommThread  ->join ();
            DisplayAndTouchCommThread->join ();
        }

        void TestBody () override { }
        void SetUp    () override { }
        void TearDown () override { }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
