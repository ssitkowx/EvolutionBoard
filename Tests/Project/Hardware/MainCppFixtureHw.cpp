///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "LoggerHw.h"
#include "MainCppFixtureHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (MainCppFixtureHw, DownloadesAndParsesWeatherData)
{
    LOGW (MODULE, "DownloadesAndParsesWeatherData");

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
    Process ();
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
