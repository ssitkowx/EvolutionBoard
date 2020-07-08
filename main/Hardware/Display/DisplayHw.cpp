///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include "LoggerHw.h"
#include "Settings.h"
#include "DisplayHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

DisplayHw::DisplayHw (Gpio & v_gpio, Spi & v_spi) : gpio (v_gpio), spi (v_spi), ili9341 (spi)
{
    LOG (MODULE, "Init /n");

    //Initialize non-SPI GPIOs
    gpio.SetPinDirection (Gpio::EPinNum::eDc  , Gpio::EPinMode::eOutput);
    gpio.SetPinDirection (Gpio::EPinNum::eRst , Gpio::EPinMode::eOutput);
    gpio.SetPinDirection (Gpio::EPinNum::eBclk, Gpio::EPinMode::eOutput);

    //Reset the display
    gpio.SetPinLevel (Gpio::EPinNum::eRst, false);
    Rtos::GetInstance ()->Delay (ONE_HUNDRED);
    gpio.SetPinLevel (Gpio::EPinNum::eRst, true);
    Rtos::GetInstance ()->Delay (ONE_HUNDRED);

    ili9341.SoftwareReset           ();
    ili9341.DisplayOff              ();
    ili9341.PowerControl1           ();
    ili9341.PowerControl2           ();
    ili9341.VCOMControl1            ();
    ili9341.VCOMControl2            ();
    ili9341.MemoryAccessControl     ();
    ili9341.PixelFormatSet          ();
    ili9341.FrameRateControl        ();
    ili9341.GammaSet                ();
    ili9341.PositiveGammaCorrection ();
    ili9341.NegativeGammaCorrection ();
    ili9341.ColumnAddressSet        ();
    ili9341.PageAddressSet          ();
    ili9341.MemoryWrite             ();
    ili9341.EntryModeSet            ();
    ili9341.DisplayFunctionControl  ();
    ili9341.SleepOut                ();
    ili9341.DisplayOn               ();

    gpio.SetPinLevel (Gpio::EPinNum::eBclk, false);
}

void DisplayHw::DrawRect (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_length, const uint16_t v_width, const uint16_t v_color)
{
    if (validateRect (v_xPos, v_yPos, v_length, v_width) == false) { LOGE (MODULE, "Rect outside display /n"); return; }

    const uint16_t rectMaxLen = Settings::GetInstance ().Lcd.Length * Settings::GetInstance ().Lcd.MaxLinesPerTransfer;
    uint16_t rect [rectMaxLen];
    memset (rect, v_color, rectMaxLen * TWO);

    uint8_t maxRects = calculateRects (v_length, v_width);
    if (maxRects == 1)
    {
        LOGV      (MODULE, "v_xPos: %u, v_yPos: %u, v_length: %u, v_width: %u end /n", v_xPos, v_yPos, v_length, v_width);
        sendLines (v_xPos, v_yPos, v_length, v_width, (uint16_t *)rect);
    }
    else
    {
        uint16_t yPos  = v_yPos;
        uint16_t width = ZERO;
        for (uint8_t rectNum = 1; rectNum < (maxRects + 1); rectNum++)
        {
            if (rectNum == maxRects)
            {
                LOGV (MODULE, "Last rect");
                width = v_width + v_yPos - yPos;

                LOGV      (MODULE, "v_xPos: %u, yPos: %u, v_length: %u, width: %u end /n", v_xPos, yPos, v_length, width);
                sendLines (v_xPos, yPos, v_length, width, (uint16_t *)rect);
                break;
            }

            LOGV      (MODULE, "v_xPos: %u, yPos: %u, v_length: %u, width: %u end /n", v_xPos, yPos, v_length, Settings::GetInstance().Lcd.MaxLinesPerTransfer);
            sendLines (v_xPos, yPos, v_length, Settings::GetInstance().Lcd.MaxLinesPerTransfer, (uint16_t *)rect);
            yPos = yPos + Settings::GetInstance().Lcd.MaxLinesPerTransfer;
        }
    }
}

void DisplayHw::DrawPicture (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data, const uint16_t v_len)
{

}

void DisplayHw::sendLines (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_length, const uint16_t v_width, const uint16_t * v_data)
{
    uint8_t data [] = { static_cast<uint8_t>(SpiHw::EFlag::eTxData),
                       (uint8_t)SpiHw::EMode::eCmd,
                        0x2A
                      };

    spi.Send (data, ONE);

    uint8_t data1 [] = { static_cast<uint8_t>(SpiHw::EFlag::eTxData),
                         (uint8_t)SpiHw::EMode::eData,
                         static_cast<uint8_t>(v_xPos >> 8),
                         static_cast<uint8_t>(v_xPos & 0xFF),
                         static_cast<uint8_t>((v_xPos + v_length) >> 8),
                         static_cast<uint8_t>((v_xPos + v_length) & 0xFF)
                       };

    spi.Send (data1, FOUR);

    uint8_t data2 [] = { SPI_TRANS_USE_TXDATA,
                         (uint8_t)SpiHw::EMode::eCmd,
                         0x2B
                       };

    spi.Send (data2, ONE);

    uint8_t data3 [] = { static_cast<uint8_t>(SpiHw::EFlag::eTxData),
                         (uint8_t)SpiHw::EMode::eData,
                         static_cast<uint8_t>(v_yPos >> 8),
                         static_cast<uint8_t>(v_yPos & 0xFF),
                         static_cast<uint8_t>((v_yPos + v_width) >> 8),
                         static_cast<uint8_t>((v_yPos + v_width) & 0xFF)
                       };

    spi.Send (data3, FOUR);

    uint8_t data4 [] = { static_cast<uint8_t>(SpiHw::EFlag::eTxData),
                         (uint8_t)SpiHw::EMode::eCmd,
                         0x2C
                       };

    spi.Send (data4, ONE);

    spi.Send16Bits (v_data, v_length * v_width);
}

bool DisplayHw::validateRect (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_length, const uint16_t v_width)
{
    if (((v_xPos + v_length) <= ZERO)                                  ||
        ((v_yPos + v_width)  <= ZERO)                                  ||
        ((v_xPos + v_length) > Settings::GetInstance ().Lcd.Length) ||
        ((v_yPos + v_width)  > Settings::GetInstance ().Lcd.Width))
    {
        return false;
    }

    return true;
}

uint8_t DisplayHw::calculateRects (const uint16_t v_length, const uint16_t v_width)
{
    double  rects    = v_width / Settings::GetInstance ().Lcd.MaxLinesPerTransfer;
    uint8_t maxRects = (uint8_t)rects;

    if ((v_width % Settings::GetInstance ().Lcd.MaxLinesPerTransfer) != ZERO) { maxRects++; }

    return maxRects;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
