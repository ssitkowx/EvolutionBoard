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
    ili9341.SendPageAddressSet          (SpiHw::EFlag::eDummy, ZERO, ZERO, (Settings::GetInstance ().Lcd.Height >> EIGHT_BYTES) & 0xFF, Settings::GetInstance ().Lcd.Height & 0xFF);
    ili9341.SendMemoryWrite             (SpiHw::EFlag::eDummy);
    ili9341.SendEntryModeSet            ();
    ili9341.SendDisplayFunctionControl  ();
    ili9341.SendSleepOut                ();
    ili9341.SendDisplayOn               ();
}

bool DisplayHw::DrawBitmap (const Rectangle & v_rect)
{
    if (validateRect (v_rect) == false) { return false; }

    uint8_t maxRects = calculateRects (v_rect.Dimension.Height);
    if (maxRects == ONE) { sendLines (v_rect); }
    else
    {
        uint16_t yPos     = ZERO;
        uint16_t height   = ZERO;
        uint16_t pixelPos = ZERO;
        for (uint8_t rectNum = ONE; rectNum <= maxRects; rectNum++)
        {
            if (rectNum == maxRects) { height = v_rect.Dimension.Height - yPos; }
            else                     { height = Config.LinesPerTransfer; }

            Rectangle rect = { };
            rect.Coordinate.X     = v_rect.Coordinate.X;
            rect.Coordinate.Y     = yPos + v_rect.Coordinate.Y;
            rect.Dimension.Width  = v_rect.Dimension.Width;
            rect.Dimension.Height = height;
            rect.Data             = &v_rect.Data [pixelPos];

            sendLines (rect);
            yPos     = yPos + height;
            pixelPos = yPos * v_rect.Dimension.Width - ONE;
        }
    }

    return true;
}

void DisplayHw::sendLines (const Rectangle & v_rect)
{
    ili9341.SendColumnAddressSet (SpiLcdHw::EFlag::eTxData, static_cast<uint8_t> (v_rect.Coordinate.X                                  >> EIGHT_BITS), static_cast<uint8_t> (v_rect.Coordinate.X & 0xFF),
                                                            static_cast<uint8_t> ((v_rect.Coordinate.X + v_rect.Dimension.Width - ONE) >> EIGHT_BITS), static_cast<uint8_t> ((v_rect.Coordinate.X + v_rect.Dimension.Width - ONE) & 0xFF));

    ili9341.SendPageAddressSet   (SpiLcdHw::EFlag::eTxData, static_cast<uint8_t> (v_rect.Coordinate.Y                                  >> EIGHT_BITS), static_cast<uint8_t> (v_rect.Coordinate.Y & 0xFF),
                                                            static_cast<uint8_t> ((v_rect.Coordinate.Y + v_rect.Dimension.Height)      >> EIGHT_BITS), static_cast<uint8_t> ((v_rect.Coordinate.Y + v_rect.Dimension.Height) & 0xFF));

    ili9341.SendMemoryWrite      (SpiLcdHw::EFlag::eTxData);
    spiLcdHw.Send                (v_rect.Data, v_rect.Dimension.Width * v_rect.Dimension.Height * sizeof (uint16_t));

}

// https://www.rapidtables.com/web/color/RGB_Color.html
uint8_t DisplayHw::getColor (const EColors v_eColor)
{
    // R [7:5],
    // B [4:3],
    // G [2:0].

    switch (v_eColor)
    {
        case EColors::eBlack  : { return 0x00; }
        case EColors::eWhite  : { return 0xFF; }
        case EColors::eRed    : { return 0xE0; }
        case EColors::eBlue   : { return 0x18; }
        case EColors::eGreen  : { return 0x07; }
        case EColors::eYellow : { return 0xE7; }
        case EColors::eCyan   : { return 0x1F; }
        case EColors::eMagneta: { return 0xF8; }
        case EColors::eGray   : { return 0x94; }
        case EColors::eMaroon : { return 0x80; }
        case EColors::eOlive  : { return 0x84; }
        case EColors::ePurple : { return 0x90; }
        case EColors::eTeal   : { return 0x14; }
        case EColors::eNavy   : { return 0x10; }
        default               : { return 0xFF; }
    };
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
