#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <thread>
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
#include "LoggerMock.h"
#include "SpiTouchHw.h"
#include "DraftsmanHw.h"
#include "SystemTimeHw.h"
#include "HttpClientHw.h"
#include "WeatherMeasureComm.h"
#include "WeatherMeasureParser.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class MainCppHwFixture : public ::testing::Test
{
    private:
        bool IsThreadInProgress = true;

    public:
        static constexpr char * MODULE = (char *)"MainCppHwFixture";

        MainCppHwFixture () = default;
        ~MainCppHwFixture () = default;

        std::shared_ptr<std::thread> BluetoothCommThread;
        std::shared_ptr<std::thread> WatherMeasureCommThread;
        std::shared_ptr<std::thread> DisplayAndTouchCommThread;

        void BluetoothProcess (void)
        {
            while (IsThreadInProgress == true)
            {
                std::this_thread::sleep_for (std::chrono::milliseconds (TEN));
            }

            LOGE (MODULE, "BluetoothProcess() Deleted.");
        }

        void WeatherMeasureProcess (void)
        {
            WiFiHw                wifiHw;
            HttpClientHw          httpClientHw;
            WeatherMeasureParser  weatherMeasureParser;
            WeatherMeasureComm    weatherMeasureComm (httpClientHw, weatherMeasureParser);
            const TimerHw::Config timerWeatherMeasureConfig = { .Divider        = SIXTEEN,
                                                                .InterruptInSec = TWENTY,
                                                                .eTimer         = Timer<TimerHw>::ETimer::e1
                                                              };

            TimerHw timerWeatherMeasureHw (timerWeatherMeasureConfig);

            while (IsThreadInProgress == true)
            {
                if (Rtos::GetInstance ()->TakeSemaphore ("TakeWeatherMeasureSemaphore") == true)
                {
                    weatherMeasureComm.Process ();
                }
            }

            LOGE (MODULE, "WeatherMeasureProcess() Deleted.");

        }

        void DisplayAndTouchProcess ()
        {
            GpioHw                       gpioHw;
            SpiLcdHw                     spiLcdHw (gpioHw);
            SpiTouchHw                   spiTouchHw;

            const DraftsmanHw::Config_t  draftsmanConfig = { .LinesPerTransfer = Settings::GetInstance ().Lcd.LinesPerTransfer,
                                                             .Dimension        = { Settings::GetInstance ().Lcd.Width,
                                                                                   Settings::GetInstance ().Lcd.Height
                                                                                 }
                                                           };

            Font                         font;
            Resources                    resources (font);
            DraftsmanHw                  draftsmanHw (draftsmanConfig, spiLcdHw, font);

            const Touch<TouchHw>::Config touchConfig = { .Histeresis = TWO,
                                                         .Time       = { FOUR,               // PressedMax, InterruptInSeconds * PressedMax
                                                                         EIGHT               // ReleasedMax
                                                                       }
                                                       };

            const TouchHw::Coefficients  touchCoefficients = { .Constant = ONE_HUNDRED_TWENTY_EIGHT,
                                                               .Width    = TWO,
                                                               .Length   = 2.68
                                                             };

            const TimerHw::Config        timerTouchConfig = { .Divider        = SIXTEEN,
                                                              .InterruptInSec = 0.01,
                                                              .eTimer         = Timer<TimerHw>::ETimer::e0
                                                            };

            TimerHw                      timerTouchHw (timerTouchConfig);
            TouchHw                      touchHw      (touchCoefficients, touchConfig, spiTouchHw);
            Action                       action       (touchHw, draftsmanHw, resources);

            while (IsThreadInProgress == true)
            {
                action.Process ();
                std::this_thread::sleep_for (std::chrono::milliseconds (ONE));
            }

            LOGE (MODULE, "DisplayAndTouchProcess() Deleted.");
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
