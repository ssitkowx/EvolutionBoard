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

class SpiHw : public Spi<SpiHw>
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

        explicit SpiHw         (spi_device_handle_t * v_handle) : handle (v_handle) { }

        void     Send          (const uint8_t  * const v_data, const uint16_t v_len);
        void     Send          (const uint16_t * const v_data, const uint16_t v_len);
        uint16_t Receive       (uint8_t        *       v_data);
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
/*
        uint32_t lcd_get_id(spi_device_handle_t spi, uint8_t v_cmd)
        {
            //get_id cmd
            //lcd_cmd(spi, 0x04);
            //lcd_cmd (spi, v_cmd);

            spi_transaction_t t;
            memset(&t, 0, sizeof(t));
            t.length=8;
            t.flags = SPI_TRANS_USE_RXDATA;
            t.user = (void*)1;

            esp_err_t ret = spi_device_polling_transmit(spi, &t);
            assert( ret == ESP_OK );

            //return *(uint32_t*)t.rx_data;
            return *(uint8_t *)t.rx_data;
        }
*/
    private:
        spi_device_handle_t * handle;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
