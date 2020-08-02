#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Spi.h"
#include "Utils.h"
#include <memory.h>
#include "driver/spi_master.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class SpiTouchHw final: public Spi
{
    static constexpr char * MODULE = (char *)"SpiTouchHw";

    public:
        enum class EFlag : uint8_t
        {
            eDio        = ZERO,
            eQio        = ONE,
            eRxData     = TWO,
            eTxData     = THREE,
            eDioQioAddr = FOUR,
            eCmd        = FIVE,
            eAddr       = SIX,
            eDummy      = SEVEN,
            eCd         = SEVEN
        };

        enum class EMode : uint8_t
        {
            eCmd  = ZERO,
            eData = ONE
        };

        template <const uint8_t DATA_LEN>
        struct Msg
        {
            uint8_t Cmd;
            uint8_t Data [DATA_LEN];
        };

        SpiTouchHw ();

        void     Send    (const uint8_t *  const v_data, const uint16_t v_len) override;
        void     Send    (const uint16_t * const v_data, const uint16_t v_len) override { }
        uint16_t Receive (uint8_t *              v_data)                       override;

        void sendCommand (SpiTouchHw::EFlag v_flag, SpiTouchHw::EMode v_mode, uint8_t v_cmd)
        {
            uint8_t cmd [] = { static_cast<uint8_t> (v_flag),
                               static_cast<uint8_t> (v_mode),
                               v_cmd
                             };

            Send (&cmd [FIRST_BYTE], ONE);
        }
/*
        template <uint8_t DATA_LEN>
        void sendData (SpiTouchHw::EFlag v_flag, SpiTouchHw::EMode v_mode, uint8_t v_data [])
        {
            uint8_t data [TWO_BYTES + DATA_LEN] = { static_cast<uint8_t> (v_flag),
                                                    static_cast<uint8_t> (v_mode)
                                                  };

            memcpy (&data [THIRD_BYTE], v_data, DATA_LEN);
            Send   (&data [FIRST_BYTE], DATA_LEN);
        }
*/
        template <uint8_t DATA_LEN>
        void receiveData (SpiTouchHw::EFlag v_flag, SpiTouchHw::EMode v_mode, uint8_t v_data [])
        {
            uint8_t data [THREE_BYTES + DATA_LEN] = { static_cast<uint8_t> (v_flag),
                                                      static_cast<uint8_t> (v_mode),
                                                      DATA_LEN
                                                    };

            Receive (&data [FIRST_BYTE]);
            memcpy  (v_data, &data [FOURTH_BYTE], DATA_LEN);
        }

    private:
        static spi_device_handle_t spi;
        const  spi_host_device_t   touchHost = HSPI_HOST;
        const  int                 dmaChan   = ONE;

};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
