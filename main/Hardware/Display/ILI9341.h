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
        uint8_t * sendData (SpiHw::EFlag v_flag, SpiHw::EMode v_mode, uint8_t v_data [])
        {
            uint8_t data [TWO_BYTES + DATA_LEN] = { static_cast<uint8_t> (v_flag),
                                                    static_cast<uint8_t> (v_mode)
                                                  };

            memcpy   (&data [THIRD_BYTE], v_data, DATA_LEN);
            return spi.Send (&data [FIRST_BYTE], DATA_LEN);
        }

    public:
        ILI9341 (Spi & v_spi): spi (v_spi) { }

        void     SoftwareReset           (void);
        void     DisplayOff              (void);
        void     PowerControl1           (void);
        void     PowerControl2           (void);
        void     VCOMControl1            (void);
        void     VCOMControl2            (void);
        void     MemoryAccessControl     (void);
        void     PixelFormatSet          (void);
        void     FrameRateControl        (void);
        void     GammaSet                (void);
        void     PositiveGammaCorrection (void);
        void     NegativeGammaCorrection (void);
        void     ColumnAddressSet        (void);
        void     PageAddressSet          (void);
        void     MemoryWrite             (void);
        void     EntryModeSet            (void);
        void     DisplayFunctionControl  (void);
        void     SleepOut                (void);
        void     DisplayOn               (void);
        uint32_t GetId                   (void);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
