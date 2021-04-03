#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include <stdint.h>
#include "Action.h"
#include "RtosHw.h"
#include "GpioHw.h"
#include "WiFiHw.h"
#include "TimerHw.h"
#include "FlashHw.h"
#include "TouchHw.h"
#include "SpiLcdHw.h"
#include "Settings.h"
#include "Resources.h"
#include "LoggerHw.h"
#include "SpiTouchHw.h"
#include "DraftsmanHw.h"
#include "SystemTimeHw.h"
#include "HttpClientHw.h"
#include "SystemEvents.h"
#include "WeatherMeasureComm.h"
#include "WeatherMeasureParser.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class MainCppHw
{
    static constexpr char * MODULE = (char *)"MainCppHw";
    protected:
        FlashHw                      flashHw;
        RtosHw                       rtosHw;
        SystemTimeHw                 systemTimeHw;

        WiFiHw                       wifiHw;
        HttpClientHw                 httpClientHw;
        WeatherMeasureParser         weatherMeasureParser;
        
        const TimerHw::Config        timerWeatherMeasureConfig  = { .Divider          = SIXTEEN,
                                                                    .InterruptInSec   = TWENTY,
                                                                    .eTimer           = Timer<TimerHw>::ETimer::e1
                                                                  };

        TimerHw                      timerWeatherMeasureHw;

        GpioHw                       gpioHw;
        SpiLcdHw                     spiLcdHw;
        SpiTouchHw                   spiTouchHw;

        const DraftsmanHw::Config_t  draftsmanConfig            = { .LinesPerTransfer = Settings::GetInstance ().Lcd.LinesPerTransfer,
                                                                    .Dimension        = { Settings::GetInstance ().Lcd.Width,
                                                                                          Settings::GetInstance ().Lcd.Height
                                                                                        }
                                                                  };

        Font                         font;
        Resources                    resources;
        DraftsmanHw                  draftsmanHw;

        const Touch<TouchHw>::Config touchConfig                = { .Histeresis       = TWO,
                                                                    .Time             = { FOUR,    // PressedMax, InterruptInSeconds * PressedMax
                                                                                          EIGHT    // ReleasedMax
                                                                                       }
                                                                  };

        const TouchHw::Coefficients  touchCoefficients          = { .Constant         = ONE_HUNDRED_TWENTY_EIGHT,
                                                                    .Width            = TWO,
                                                                    .Length           = 2.68
                                                                  };

        const TimerHw::Config        timerTouchConfig           = { .Divider          = SIXTEEN,
                                                                    .InterruptInSec   = 0.01,
                                                                    .eTimer           = Timer<TimerHw>::ETimer::e0
                                                                  };

        TimerHw                      timerTouchHw;
        TouchHw                      touchHw;

    public:
        class Action                 Action;
        class WeatherMeasureComm     WeatherMeasureComm;

        virtual bool IsThreadInProgress (void) = 0;

        MainCppHw ();
        virtual ~MainCppHw () = default;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
