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

class SpiHw : public Spi
{
    static constexpr char * MODULE = (char *)"SpiHw";

    public:
        enum class EFlag : uint8_t
        {
            eDio        = ONE << ZERO,
            eQio        = ONE << ONE,
            eRxData     = ONE << TWO,
            eTxData     = ONE << THREE,
            eDioQioAddr = ONE << FOUR,
            eCmd        = ONE << FIVE,
            eAddr       = ONE << SIX,
            eDummy      = ONE << SEVEN,
            eCd         = ONE << SEVEN
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

        explicit SpiHw (spi_device_handle_t * v_handle) : handle (v_handle) { }

        void     Send          (const uint8_t  * const v_data, const uint16_t v_len                          ) override;
        void     Send          (const uint16_t * const v_data, const uint16_t v_len                          ) override;
        uint16_t Receive       (uint8_t        *       v_data                                                ) override;
        void     SendCommand   (const SpiHw::EFlag     v_flag, const SpiHw::EMode v_mode, const uint8_t v_cmd);

        template <uint8_t DATA_LEN>
        void ReceiveData (const SpiHw::EFlag v_flag, const SpiHw::EMode v_mode, uint8_t v_data [])
        {
            uint8_t data [THREE_BYTES + DATA_LEN] = { static_cast<uint8_t> (v_flag),
                                                      static_cast<uint8_t> (v_mode),
                                                      DATA_LEN
                                                    };

            Receive (&data [FIRST_BYTE]);
            memcpy  (v_data, &data [FOURTH_BYTE], DATA_LEN);
        }


        template <uint8_t DATA_LEN>
        void SendData (const SpiHw::EFlag v_flag, const SpiHw::EMode v_mode, const uint8_t v_data [])
        {
            uint8_t data [TWO_BYTES + DATA_LEN] = { static_cast<uint8_t> (v_flag),
                                                    static_cast<uint8_t> (v_mode)
                                                  };

            memcpy (&data [THIRD_BYTE], v_data, DATA_LEN);
            Send   (&data [FIRST_BYTE], DATA_LEN);
        }

    private:
        spi_device_handle_t * handle;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
