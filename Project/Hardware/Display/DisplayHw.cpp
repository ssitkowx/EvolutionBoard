///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include "GpioHw.h"
#include "LoggerHw.h"
#include "Settings.h"
#include "DisplayHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

DisplayHw::DisplayHw (Gpio & v_gpio, const Display::Configuration v_config) : Display (v_config),
                                                                              gpio    (v_gpio),
                                                                              ili9341 (spiLcdHw)
{
    LOG (MODULE, "Init./n");

    // Initialize non-SPI GPIOs
    gpio.SetPinDirection (static_cast<uint16_t> (GpioHw::ELcd::eDc) , static_cast<uint16_t> (GpioHw::EPinMode::eOutput));
    gpio.SetPinDirection (static_cast<uint16_t> (GpioHw::ELcd::eRst), static_cast<uint16_t> (GpioHw::EPinMode::eOutput));

    //Reset the display
    gpio.SetPinLevel  (static_cast<uint16_t> (GpioHw::ELcd::eRst), false);
    Rtos::GetInstance ()->Delay (ONE_HUNDRED);
    gpio.SetPinLevel  (static_cast<uint16_t> (GpioHw::ELcd::eRst), true);
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
}

bool DisplayHw::DrawText (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data, const uint16_t v_len, const Display::EColors eColor)
{
    return false;
}

bool DisplayHw::DrawPicture (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data, const uint16_t v_len)
{
    return false;
}

void DisplayHw::sendLines (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length, const uint16_t * const v_data)
{
    ili9341.SendColumnAddressSet (SpiLcdHw::EFlag::eTxData, static_cast<uint8_t> (v_xPos              >> EIGHT_BITS), static_cast<uint8_t> (v_xPos & 0xFF),
                                                            static_cast<uint8_t> ((v_xPos + v_width)  >> EIGHT_BITS), static_cast<uint8_t> ((v_xPos + v_width) & 0xFF));

    ili9341.SendPageAddressSet   (SpiLcdHw::EFlag::eTxData, static_cast<uint8_t> (v_yPos              >> EIGHT_BITS), static_cast<uint8_t> (v_yPos & 0xFF),
                                                            static_cast<uint8_t> ((v_yPos + v_length) >> EIGHT_BITS), static_cast<uint8_t> ((v_yPos + v_length) & 0xFF));

    ili9341.SendMemoryWrite      (SpiLcdHw::EFlag::eTxData);
    spiLcdHw.Send                (v_data, v_width * v_length);
}



uint8_t DisplayHw::getColor (const EColors v_eColor)
{
    // B [7:5],
    // R [4:3],
    // G [2:0].

    switch (v_eColor)
    {
        case EColors::eBlack  : { return 0x00; }
        case EColors::eWhite  : { return 0xFF; }
        case EColors::eRed    : { return 0x18; }
        case EColors::eLime   : { return 0x07; }
        case EColors::eBlue   : { return 0xE0; }
        case EColors::eYellow : { return 0x1F; }
        case EColors::eCyan   : { return 0xE7; }
        case EColors::eMagneta: { return 0xF8; }
        case EColors::eSilver : { return 0xD6; }
        case EColors::eGray   : { return 0x94; }
        case EColors::eMaroon : { return 0x10; }
        case EColors::eOlive  : { return 0x14; }
        case EColors::eGreen  : { return 0x04; }
        case EColors::ePurple : { return 0x90; }
        case EColors::eTeal   : { return 0x84; }
        case EColors::eNavy   : { return 0x80; }
        default               : { return 0xFF; }
    };
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
