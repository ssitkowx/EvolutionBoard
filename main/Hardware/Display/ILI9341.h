#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "SpiHw.h"
#include "Utils.h"
#include <stdint.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class ILI9341
{
    private:
        Spi & spi;

        template <const uint8_t DATA_LEN>
        struct Msg
        {
            uint8_t Cmd;
            uint8_t Data [DATA_LEN];
        };

        void sendCommand (SpiHw::EFlag v_flag, SpiHw::EMode v_mode, uint8_t v_cmd);

        template <uint8_t DATA_LEN>
        void sendData (SpiHw::EFlag v_flag, SpiHw::EMode v_mode, uint8_t v_data [])
        {
            uint8_t data [TWO_BYTES + DATA_LEN] = { static_cast<uint8_t> (v_flag),
                                                    static_cast<uint8_t> (v_mode)
                                                  };

            memcpy (&data [THIRD_BYTE], v_data, DATA_LEN);
            spi.Send (&data [FIRST_BYTE], DATA_LEN);
        }

        template <uint8_t DATA_LEN>
        void receiveData (SpiHw::EFlag v_flag, SpiHw::EMode v_mode, uint8_t v_data [])
        {
            uint8_t data [TWO_BYTES + DATA_LEN] = { static_cast<uint8_t> (v_flag),
                                                    static_cast<uint8_t> (v_mode)
                                                  };

            memcpy (&data [THIRD_BYTE], v_data, DATA_LEN);
            spi.Receive (&data [FIRST_BYTE], DATA_LEN);
        }

    public:
        ILI9341 (Spi & v_spi): spi (v_spi) { }

        void     SendSoftwareReset           (void);
        void     SendDisplayOff              (void);
        void     SendPowerControl1           (void);
        void     SendPowerControl2           (void);
        void     SendVCOMControl1            (void);
        void     SendVCOMControl2            (void);
        void     SendMemoryAccessControl     (void);
        void     SendPixelFormatSet          (void);
        void     SendFrameRateControl        (void);
        void     SendGammaSet                (void);
        void     SendPositiveGammaCorrection (void);
        void     SendNegativeGammaCorrection (void);
        void     SendEntryModeSet            (void);
        void     SendDisplayFunctionControl  (void);
        void     SendSleepOut                (void);
        void     SendDisplayOn               (void);
        void     SendMemoryWrite             (const SpiHw::EFlag v_eFlag);
        void     SendColumnAddressSet        (const SpiHw::EFlag v_eFlag, const uint8_t v_scH, const uint8_t v_scL,
                                                                          const uint8_t v_ecH, const uint8_t v_ecL);
        void     SendPageAddressSet          (const SpiHw::EFlag v_eFlag, const uint8_t v_spH, const uint8_t v_spL,
                                                                          const uint8_t v_epH, const uint8_t v_epL);
        uint32_t ReceiveGetId                (void);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
