///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "SpiHw.h"
#include "LoggerHw.h"
#include "Settings.h"
#include "driver/gpio.h"

#include "Rtos.h"
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static uint8_t getFlag (SpiHw::EFlag v_flag)
{
    if (v_flag == SpiHw::EFlag::eDummy) { return ZERO; }
    return (ONE << static_cast<uint8_t> (v_flag));
}

void SpiHw::Send (const uint8_t * const v_data, const uint16_t v_len)
{
    if (v_len == ZERO) { LOGE (MODULE, "Data length is empty."); return; }

    spi_transaction_t transaction = { };
    memset (&transaction, ZERO, sizeof (transaction));

    uint8_t flags = getFlag (static_cast<SpiHw::EFlag>(v_data [FIRST_BYTE]));
    uint8_t user  = v_data [SECOND_BYTE];

    transaction.flags  = flags;
    transaction.user   = reinterpret_cast<void *>(user);
    transaction.length = v_len * EIGHT_BITS;

    if (flags == SPI_TRANS_USE_TXDATA)
    {
        transaction.tx_data [FIRST_BYTE] = v_data [THIRD_BYTE];
        if (user == ONE)
        {
            transaction.tx_data [SECOND_BYTE] = v_data [FOURTH_BYTE];
            transaction.tx_data [THIRD_BYTE]  = v_data [FIFTH_BYTE];
            transaction.tx_data [FOURTH_BYTE] = v_data [SIXTH_BYTE];
        }
    }
    else { transaction.tx_buffer = &v_data [THIRD_BYTE]; }

    esp_err_t status = spi_device_polling_transmit (*handle, &transaction);
    assert (status == ESP_OK);
}

void SpiHw::Send (const uint16_t * const v_data, const uint16_t v_len)
{
    if (v_len == ZERO) { LOGE (MODULE, "Data length is empty."); return; }

    spi_transaction_t transaction = { };
    memset (&transaction, ZERO, sizeof (transaction));

    transaction.flags     = ZERO;
    transaction.user      = (void *)SpiHw::EMode::eData;
    transaction.length    = v_len * EIGHT_BITS;
    transaction.tx_buffer = &v_data [ZERO];

    esp_err_t status = spi_device_polling_transmit (*handle, &transaction);
    assert (status == ESP_OK);
}

uint16_t SpiHw::Receive (uint8_t * v_data)
{
    static spi_transaction_t transaction = { };
    memset (&transaction, ZERO, sizeof (transaction));

    transaction.flags  = getFlag (static_cast<SpiHw::EFlag>(v_data [FIRST_BYTE]));
    transaction.user   = reinterpret_cast<void *>(v_data [SECOND_BYTE]);
    transaction.length = v_data [THIRD_BYTE] * EIGHT_BITS;

    esp_err_t status = spi_device_polling_transmit (*handle, &transaction);
    assert (status == ESP_OK);

    v_data [FOURTH_BYTE] = transaction.rx_data [FIRST_BYTE];
    return transaction.length;
}

void SpiHw::SendCommand (const SpiHw::EFlag v_flag, const SpiHw::EMode v_mode, const uint8_t v_cmd)
{
    uint8_t cmd [] = { static_cast<uint8_t> (v_flag),
                       static_cast<uint8_t> (v_mode),
                       v_cmd
                     };

    Send (&cmd [FIRST_BYTE], ONE);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
