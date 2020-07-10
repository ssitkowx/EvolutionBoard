///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Spi.h"
#include "Rtos.h"
#include "SpiHw.h"
#include "GpioHw.h"
#include "LoggerHw.h"
#include "Settings.h"
#include "DisplayHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

DisplayHw::DisplayHw (Gpio & v_gpio, Spi & v_spi) : gpio (v_gpio), spi (v_spi), ili9341 (spi)
{
    LOG (MODULE, "Init./n");

    //Initialize non-SPI GPIOs
    gpio.SetPinDirection (static_cast<uint16_t> (GpioHw::EPinNum::eDc)  , static_cast<uint16_t> (GpioHw::EPinMode::eOutput));
    gpio.SetPinDirection (static_cast<uint16_t> (GpioHw::EPinNum::eRst) , static_cast<uint16_t> (GpioHw::EPinMode::eOutput));
    gpio.SetPinDirection (static_cast<uint16_t> (GpioHw::EPinNum::eBclk), static_cast<uint16_t> (GpioHw::EPinMode::eOutput));

    //Reset the display
    gpio.SetPinLevel  (static_cast<uint16_t> (GpioHw::EPinNum::eRst), false);
    Rtos::GetInstance ()->Delay (ONE_HUNDRED);
    gpio.SetPinLevel  (static_cast<uint16_t> (GpioHw::EPinNum::eRst), true);
    Rtos::GetInstance ()->Delay (ONE_HUNDRED);

    ili9341.SendSoftwareReset           ();
    ili9341.SendDisplayOff              ();
    ili9341.SendPowerControl1           ();
    ili9341.SendPowerControl2           ();
    ili9341.SendVCOMControl1            ();
    ili9341.SendVCOMControl2            ();
    ili9341.SendMemoryAccessControl     ();
    ili9341.SendPixelFormatSet          ();
    ili9341.SendFrameRateControl        ();
    ili9341.SendGammaSet                ();
    ili9341.SendPositiveGammaCorrection ();
    ili9341.SendNegativeGammaCorrection ();
    ili9341.SendColumnAddressSet        (SpiHw::EFlag::eDummy, ZERO, ZERO, (Settings::GetInstance ().Lcd.Width  >> EIGHT_BYTES) & 0xFF, Settings::GetInstance ().Lcd.Width  & 0xFF);
    ili9341.SendPageAddressSet          (SpiHw::EFlag::eDummy, ZERO, ZERO, (Settings::GetInstance ().Lcd.Length >> EIGHT_BYTES) & 0xFF, Settings::GetInstance ().Lcd.Length & 0xFF);
    ili9341.SendMemoryWrite             (SpiHw::EFlag::eDummy);
    ili9341.SendEntryModeSet            ();
    ili9341.SendDisplayFunctionControl  ();
    ili9341.SendSleepOut                ();
    ili9341.SendDisplayOn               ();

    gpio.SetPinLevel (static_cast<uint16_t> (GpioHw::EPinNum::eBclk), false);
}

void DisplayHw::DrawRect (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length, const uint16_t v_color)
{
    if (validateRect (v_xPos, v_yPos, v_width, v_length) == false) { LOGE (MODULE, "Rect outside display./n"); return; }

    uint16_t rect [Settings::GetInstance ().Lcd.Width * Settings::GetInstance ().Lcd.MaxLinesPerTransfer] = { };
    uint8_t  maxRects = calculateRects (v_length);

    if (maxRects == ONE)
    {
        //LOGD      (MODULE, "One rect: v_xPos: %u, v_yPos: %u, v_width: %u, v_length: %u end./n", v_xPos, v_yPos, v_width, v_length);
        sendLines (v_xPos, v_yPos, v_width, v_length, static_cast <uint16_t *> (rect));
    }
    else
    {
        uint16_t yPos  = v_yPos;
        uint16_t length = ZERO;
        for (uint8_t rectNum = ONE; rectNum <= maxRects; rectNum++)
        {
            if (rectNum == maxRects)
            {
                //LOGD      (MODULE, "Last rect: v_xPos: %u, yPos: %u, v_width: %u, length: %u end./n", v_xPos, yPos, v_width, length);
                length = v_length + v_yPos - yPos;
                sendLines (v_xPos, yPos, v_width, length, static_cast <uint16_t *> (rect));
            }
            else
            {
                //LOGD      (MODULE, "Rect: v_xPos: %u, yPos: %u, v_width: %u, length: %u end /n", v_xPos, yPos, v_width, Settings::GetInstance().Lcd.MaxLinesPerTransfer);
                sendLines (v_xPos, yPos, v_width, Settings::GetInstance().Lcd.MaxLinesPerTransfer, static_cast <uint16_t *> (rect));
                yPos = yPos + Settings::GetInstance().Lcd.MaxLinesPerTransfer;
            }
        }
    }
}

void DisplayHw::DrawText (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data, const uint16_t v_len)
{

}

void DisplayHw::DrawPicture (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data, const uint16_t v_len)
{

}

void DisplayHw::sendLines (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length, const uint16_t * const v_data)
{
    ili9341.SendColumnAddressSet (SpiHw::EFlag::eTxData, static_cast<uint8_t> (v_xPos              >> EIGHT_BITS), static_cast<uint8_t> (v_xPos & 0xFF),
                                                         static_cast<uint8_t> ((v_xPos + v_width)  >> EIGHT_BITS), static_cast<uint8_t> ((v_xPos + v_width) & 0xFF));

    ili9341.SendPageAddressSet   (SpiHw::EFlag::eTxData, static_cast<uint8_t> (v_yPos              >> EIGHT_BITS), static_cast<uint8_t> (v_yPos & 0xFF),
                                                         static_cast<uint8_t> ((v_yPos + v_length) >> EIGHT_BITS), static_cast<uint8_t> ((v_yPos + v_length) & 0xFF));

    ili9341.SendMemoryWrite      (SpiHw::EFlag::eTxData);
    spi.Send                     (v_data, v_width * v_length);
}

bool DisplayHw::validateRect (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length)
{
    return (((v_xPos  + v_width)  > Settings::GetInstance ().Lcd.Width)  ||
            ((v_yPos  + v_length) > Settings::GetInstance ().Lcd.Length)) ? false : true;
}

uint8_t DisplayHw::calculateRects (const uint16_t v_length)
{
    double  rects    = v_length / Settings::GetInstance ().Lcd.MaxLinesPerTransfer;
    uint8_t maxRects = static_cast <uint8_t> (rects);

    if ((v_length % Settings::GetInstance ().Lcd.MaxLinesPerTransfer) != ZERO) { maxRects++; }

    return maxRects;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////