#pragma once

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class MainCppHw
{
    private:
        bool isThreadInProgress = true;

    public:
        static constexpr char * MODULE = (char *)"MainCppHw";

        MainCppHw ();
        ~MainCppHw () = default;

        void BluetoothProcess       (void);
        void WeatherMeasureProcess  (void);
        void DisplayAndTouchProcess (void);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
