///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "LoggerHw.h"
#include "MainCppHw.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (MainCppHwFixture, MainCppHw)
{
    LOGW (MODULE, "MainCppHw");

    static SystemTimeHw systemTimeHw;
    SET_SYSTEM_TIME_INST (&systemTimeHw);

    static RtosHw rtosHw;
    SET_RTOS_INST (&rtosHw);

    FlashHw flashHw;
    /*
    WiFi::Mode.StaConnected = true;
    Settings::GetInstance ().MicorTigWelderMsg.Filter.AcceptMeasureNumber = ONE;
    Settings::GetInstance ().System.Time.Previous = 1582138800000;
    Settings::GetInstance ().System.Time.Current = 1582097045000;

    ON_CALL (oMicorTigWelderCommMock, IsMeasureEnabled ()).WillByDefault (Return (true));
    ON_CALL (oHttpClientMock, Init ()).WillByDefault (Return (true));
    ON_CALL (oHttpClientMock, Perform ()).WillByDefault (Return (ZERO));
    EXPECT_CALL (oCanMock, Receive (_)).WillRepeatedly (Return (false));
    EXPECT_CALL (oRtosMock, TakeAzureDataUpdateSemaphore ()).WillRepeatedly (Return (false));

    InSequence sequence;
    for (auto & canMsgRespMeasureNum : CanMsgRespMeasure)
    {
        EXPECT_CALL (oCanMock, Receive (_)).WillOnce (DoAll (SetCanResponse <ZERO> (canMsgRespMeasureNum.second ()),
                                                      Return (true)));
    }

    EXPECT_CALL (oRtosMock, TakeAzureDataUpdateSemaphore ()).WillOnce (Return (true));
    */
    std::shared_ptr<std::thread> bluetoothThread       (new std::thread (&MainCppHwFixture::BluetoothProcess      , this));
    std::shared_ptr<std::thread> watherMeasureThread   (new std::thread (&MainCppHwFixture::WeatherMeasureProcess , this));
    std::shared_ptr<std::thread> displayAndTouchThread (new std::thread (&MainCppHwFixture::DisplayAndTouchProcess, this));

    BluetoothCommThread       = std::move (bluetoothThread);
    WatherMeasureCommThread   = std::move (watherMeasureThread);
    DisplayAndTouchCommThread = std::move (displayAndTouchThread);

    BluetoothCommThread      ->join ();
    WatherMeasureCommThread  ->join ();
    DisplayAndTouchCommThread->join ();
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
