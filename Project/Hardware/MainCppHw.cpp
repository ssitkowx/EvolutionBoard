///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "RtosHw.h"
#include <stdint.h>
#include "GpioHw.h"
#include "WiFiHw.h"
#include "FLashHw.h"
#include "Settings.h"
#include "SpiLcdHw.h"
#include "LoggerHw.h"
#include "DisplayHw.h"
#include "SpiTouchHw.h"
#include "SystemTimeHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static constexpr char * MODULE = (char *)"MainCppHw";

TaskHandle_t DisplayAndTouchTaskHandle;
TaskHandle_t NetworkConnectionTaskHandle;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


template <const uint8_t DATA_LEN>
struct Msg
{
    uint8_t Cmd;
    uint8_t Data [DATA_LEN];
};

void sendCommand (Spi & v_spi, SpiTouchHw::EFlag v_flag, SpiTouchHw::EMode v_mode, uint8_t v_cmd)
{
    uint8_t cmd [] = { static_cast<uint8_t> (v_flag),
                       static_cast<uint8_t> (v_mode),
                       v_cmd
                     };

    v_spi.Send (&cmd [FIRST_BYTE], ONE);
}

template <uint8_t DATA_LEN>
void sendData (Spi & v_spi, SpiTouchHw::EFlag v_flag, SpiTouchHw::EMode v_mode, uint8_t v_data [])
{
    uint8_t data [TWO_BYTES + DATA_LEN] = { static_cast<uint8_t> (v_flag),
                                            static_cast<uint8_t> (v_mode)
                                          };

    memcpy     (&data [THIRD_BYTE], v_data, DATA_LEN);
    v_spi.Send (&data [FIRST_BYTE], DATA_LEN);
}

template <uint8_t DATA_LEN>
void receiveData (Spi & v_spi, SpiTouchHw::EFlag v_flag, SpiTouchHw::EMode v_mode, uint8_t v_data [])
{
    uint8_t data [THREE_BYTES + DATA_LEN] = { static_cast<uint8_t> (v_flag),
                                              static_cast<uint8_t> (v_mode),
                                              DATA_LEN
                                            };

    v_spi.Receive (&data [FIRST_BYTE]);
    memcpy      (v_data, &data [FOURTH_BYTE], DATA_LEN);
}

extern "C"
{
    void DisplayAndTouchProcess    (void * v_params);
    void InternetConnectionProcess (void * v_params);

    void MainCppHw (void)
    {
        FlashHw flashHw;

        //static LoggerHw loggerHw;
        //SET_LOGGER_INST(std::make_shared<LoggerHw>(loggerHw));

        static RtosHw rtosHw;
        SET_RTOS_INST(&rtosHw);

        static SystemTimeHw systemTimeHw;
        SET_SYSTEM_TIME_INST(&systemTimeHw);

        Rtos::GetInstance()->TaskCreate (DisplayAndTouchProcess,
                                         "DisplayAndTouch",
                                         Settings::GetInstance ().StackDepth.DisplayAndTouch,
                                         static_cast <uint32_t> (RtosHw::EThreadPriority::eNormal),
                                         DisplayAndTouchTaskHandle);

        Rtos::GetInstance()->TaskCreate (&InternetConnectionProcess,
                                         "InternetConnection",
                                         Settings::GetInstance ().StackDepth.InterntConnection,
                                         static_cast <uint32_t> (RtosHw::EThreadPriority::eAboveNormal),
                                         NetworkConnectionTaskHandle);
    }

    enum class ECoordinates : uint8_t
    {
        eX  = 0xD0,
        eY  = 0x90,
        eZ1 = 0xB0,
        eZ2 = 0xC0
    };

    uint16_t GetPos (Spi & v_spi, ECoordinates v_coordinates)
    {
        Msg <TWO_BYTES> msg;
        msg.Cmd = static_cast <uint8_t> (v_coordinates);
        memset (msg.Data, ZERO, TWO_BYTES);

        sendCommand             (v_spi, SpiTouchHw::EFlag::eDummy , SpiTouchHw::EMode::eCmd , msg.Cmd);
        receiveData <TWO_BYTES> (v_spi, SpiTouchHw::EFlag::eRxData, SpiTouchHw::EMode::eData, msg.Data);

        //return (msg.Data [FIRST_BYTE] << FOUR_BITS) + msg.Data [SECOND_BYTE];
        return msg.Data [FIRST_BYTE];
    }

    void DisplayAndTouchProcess (void * v_params)
    {

        GpioHw     gpioHw;
        SpiLcdHw   spiLcdHw;
        SpiTouchHw spiTouchHw;
        DisplayHw  display (gpioHw, spiLcdHw);

        uint16_t xPos   = 50;
        uint16_t yPos   = 50;
        uint16_t width  = 100;
        uint16_t length = 100;

        display.DrawRect (xPos        , yPos, width, length, Display::EColors::ePurple);
        display.DrawRect (xPos + width, yPos, width, length, Display::EColors::eMagneta);

        //////////////////////// Touch ////////////////////

        while (true)
        {
            if (Rtos::GetInstance ()->TakeSemaphore ("TakeTouchUpdateSemaphore") == true)
            {
                LOGV (MODULE, "X  position %u", GetPos (spiTouchHw, ECoordinates::eX));
                LOGD (MODULE, "Y  position %u", GetPos (spiTouchHw, ECoordinates::eY));
                LOGI (MODULE, "Z1 position %u", GetPos (spiTouchHw, ECoordinates::eZ1));
                LOGE (MODULE, "Z2 position %u", GetPos (spiTouchHw, ECoordinates::eZ2));

                Rtos::GetInstance ()->Delay (1000);

                //LOGD (MODULE, "Touch touched");
            }

/*
            /////////////////// Z1 position //////////////////////////
            msg.Cmd = 0xB9;
            memset (msg.Data, 0, ONE_BYTE);
            // Second byte
            // RIM [7],
            // DPI [6:4],
            // DBI [2:0]

            sendCommand            (spiTouchHw, SpiTouchHw::EFlag::eDummy , SpiTouchHw::EMode::eCmd , msg.Cmd);
            receiveData <ONE_BYTE> (spiTouchHw, SpiTouchHw::EFlag::eRxData, SpiTouchHw::EMode::eData, msg.Data);
            LOGV (MODULE, "Z1 position %u", msg.Data [FIRST_BYTE]);
            Rtos::GetInstance ()->Delay (1000);

            /////////////////// Z2 position //////////////////////////
            msg.Cmd = 0xC9;
            memset (msg.Data, 0, ONE_BYTE);
            // Second byte
            // RIM [7],
            // DPI [6:4],
            // DBI [2:0]

            sendCommand            (spiTouchHw, SpiTouchHw::EFlag::eDummy , SpiTouchHw::EMode::eCmd , msg.Cmd);
            receiveData <ONE_BYTE> (spiTouchHw, SpiTouchHw::EFlag::eRxData, SpiTouchHw::EMode::eData, msg.Data);
            LOGV (MODULE, "Z2 position %u", msg.Data [FIRST_BYTE]);
            Rtos::GetInstance ()->Delay (1000);

            /////////////////// X position //////////////////////////
            msg.Cmd = 0xD9;
            memset (msg.Data, 0, ONE_BYTE);
            // Second byte
            // RIM [7],
            // DPI [6:4],
            // DBI [2:0]

            sendCommand            (spiTouchHw, SpiTouchHw::EFlag::eDummy , SpiTouchHw::EMode::eCmd , msg.Cmd);
            receiveData <ONE_BYTE> (spiTouchHw, SpiTouchHw::EFlag::eRxData, SpiTouchHw::EMode::eData, msg.Data);
            LOGV (MODULE, "X position %u", msg.Data [FIRST_BYTE]);
            Rtos::GetInstance ()->Delay (1000);
*/
            //displayAndTouch.Process ();

            //LOGI (MODULE, "DisplayAndTouchProcess. Stack left: %u", Rtos::GetInstance ()->GetCurrentStackSize ("DisplayAndTouch"));
        }

        vTaskDelete (NULL);
        LOGE        (MODULE, "DisplayAndTouchProcess() Deleted.");
    }

    void InternetConnectionProcess (void * v_params)
    {
        WiFiHw wifiHw;

        while (true)
        {
            //LOGV (MODULE, "InternetConnectionProcess. Stack left: %u", Rtos::GetInstance ()->GetCurrentStackSize ("InternetConnectionProcess"));
        }

        /*
        HttpClientHw      httpClientHw;
        MicorTigAzureComm micorTigAzureComm (httpClientHw);

        while (true)
        {
            if (Rtos::GetInstance ()->TakeAzureDataUpdateSemaphore () == true)
            {
                internetConnection.Process ();
            }
        }
*/
        vTaskDelete (NULL);
        LOGE        (MODULE, "InternetConnectionProcess() Deleted./n");

    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
