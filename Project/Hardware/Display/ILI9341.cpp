///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include "SpiHw.h"
#include "ILI9341.h"
#include "Settings.h"
#include "LoggerHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ILI9341::ILI9341 (SpiLcdHw & v_spiLcdHw) : spiLcdHw (v_spiLcdHw)
{
    LOG (MODULE, "Init./n");

    sendSoftwareReset           ();
    sendDisplayOff              ();
    sendPowerControl1           ();
    sendPowerControl2           ();
    sendVCOMControl1            ();
    sendVCOMControl2            ();
    sendMemoryAccessControl     ();
    sendPixelFormatSet          ();
    sendFrameRateControl        ();
    sendGammaSet                ();
    sendPositiveGammaCorrection ();
    sendNegativeGammaCorrection ();
    sendColumnAddressSet        (SpiHw::EFlag::eDummy, ZERO, ZERO, (Settings::GetInstance ().Lcd.Width  >> EIGHT_BYTES) & 0xFF, Settings::GetInstance ().Lcd.Width  & 0xFF);
    sendPageAddressSet          (SpiHw::EFlag::eDummy, ZERO, ZERO, (Settings::GetInstance ().Lcd.Height >> EIGHT_BYTES) & 0xFF, Settings::GetInstance ().Lcd.Height & 0xFF);
    sendMemoryWrite             (SpiHw::EFlag::eDummy);
    sendEntryModeSet            ();
    sendDisplayFunctionControl  ();
    sendSleepOut                ();
    sendDisplayOn               ();
}

void ILI9341::SendLines (const Bitmap & v_bitmap)
{
    sendColumnAddressSet (SpiLcdHw::EFlag::eTxData, static_cast<uint8_t> (v_bitmap.Coordinate.X                                    >> EIGHT_BITS), static_cast<uint8_t> (v_bitmap.Coordinate.X & 0xFF),
                                                    static_cast<uint8_t> ((v_bitmap.Coordinate.X + v_bitmap.Dimension.Width - ONE) >> EIGHT_BITS), static_cast<uint8_t> ((v_bitmap.Coordinate.X + v_bitmap.Dimension.Width - ONE) & 0xFF));

    sendPageAddressSet   (SpiLcdHw::EFlag::eTxData, static_cast<uint8_t> (v_bitmap.Coordinate.Y                                    >> EIGHT_BITS), static_cast<uint8_t> (v_bitmap.Coordinate.Y & 0xFF),
                                                    static_cast<uint8_t> ((v_bitmap.Coordinate.Y + v_bitmap.Dimension.Height)      >> EIGHT_BITS), static_cast<uint8_t> ((v_bitmap.Coordinate.Y + v_bitmap.Dimension.Height) & 0xFF));

    sendMemoryWrite      (SpiLcdHw::EFlag::eTxData);
    spiLcdHw.Send        (v_bitmap.Data, v_bitmap.Dimension.Width * v_bitmap.Dimension.Height * sizeof (uint16_t));

}


void ILI9341::sendSoftwareReset (void)
{
    SpiHw::Msg <ZERO_BYTES> msg;
    msg.Cmd = 0x01;
    spiLcdHw.SendCommand (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd, msg.Cmd);
    Rtos::GetInstance    ()->DelayInMs (ONE_HUNDRED);
}

uint8_t ILI9341::receiveDisplayPixelFormat (void)
{
    SpiHw::Msg <TWO_BYTES> msg;
    msg.Cmd = 0x0C;
    memset (msg.Data, ZERO, TWO_BYTES);
    // Second byte
    // RIM [7],
    // DPI [6:4],
    // DBI [2:0]

    spiLcdHw.SendCommand            (SpiHw::EFlag::eDummy , SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.ReceiveData<TWO_BYTES> (SpiHw::EFlag::eRxData, SpiHw::EMode::eData, msg.Data);
    return msg.Data [SECOND_BYTE];
}

void ILI9341::sendDisplayOff (void)
{
    SpiHw::Msg <ZERO_BYTES> msg;
    msg.Cmd = 0x28;
    spiLcdHw.SendCommand (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd, msg.Cmd);
}

void ILI9341::sendPowerControl1 (void)
{
    SpiHw::Msg <ONE_BYTE> msg;
    msg.Cmd               = 0xC0;
    msg.Data [FIRST_BYTE] = 0x26;    // VRH [5:0],

    spiLcdHw.SendCommand         (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <ONE_BYTE> (SpiHw::EFlag::eDummy, SpiHw::EMode::eData, msg.Data);
}

void ILI9341::sendPowerControl2 (void)
{
    SpiHw::Msg <ONE_BYTE> msg;
    msg.Cmd               = 0xC1;
    msg.Data [FIRST_BYTE] = 0x11;    // BT [2:0], VCIx2, VGH = VCI x 7, -VCI x 3.

    spiLcdHw.SendCommand         (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <ONE_BYTE> (SpiHw::EFlag::eDummy, SpiHw::EMode::eData, msg.Data);
}

void ILI9341::sendVCOMControl1 (void)
{
    SpiHw::Msg <TWO_BYTES> msg;
    msg.Cmd                = 0xC5;
    msg.Data [FIRST_BYTE]  = 0x35;    // VMH [6:0],
    msg.Data [SECOND_BYTE] = 0x3E;    // VML [6:0],

    spiLcdHw.SendCommand          (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <TWO_BYTES> (SpiHw::EFlag::eDummy, SpiHw::EMode::eData, msg.Data);
}

void ILI9341::sendVCOMControl2 (void)
{
    SpiHw::Msg <ONE_BYTE> msg;
    msg.Cmd               = 0xC7;
    msg.Data [FIRST_BYTE] = 0xBE;    // nVM [7], VMF [6:0]

    spiLcdHw.SendCommand         (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <ONE_BYTE> (SpiHw::EFlag::eDummy, SpiHw::EMode::eData, msg.Data);
}

void ILI9341::sendMemoryAccessControl (void)
{
    SpiHw::Msg <ONE_BYTE> msg;
    msg.Cmd               = 0x36;
    msg.Data [FIRST_BYTE] = 0x88;    // MY  [7] = 1,
                                     // MX  [6] = 0,
                                     // MV  [5] = 0,
                                     // ML  [4] = 0,
                                     // BGR [3] = 1,
                                     // MH  [2] = 0,
                                     //     [1]   0,
                                     //     [0]   0.

    spiLcdHw.SendCommand         (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <ONE_BYTE> (SpiHw::EFlag::eDummy, SpiHw::EMode::eData, msg.Data);
}

void ILI9341::sendPixelFormatSet (void)
{
    SpiHw::Msg <ONE_BYTE> msg;
    msg.Cmd                = 0x3A;
    msg.Data [FIRST_BYTE]  = 0x55;    // DPI [6:4], DBI [2:0],
                                      // 16bits / pixel.

    spiLcdHw.SendCommand         (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <ONE_BYTE> (SpiHw::EFlag::eDummy, SpiHw::EMode::eData, msg.Data);
}

void ILI9341::sendFrameRateControl (void)
{
    SpiHw::Msg <TWO_BYTES> msg;
    msg.Cmd                = 0xB1;
    msg.Data [FIRST_BYTE]  = 0x00;    // DIVA [1:0],
    msg.Data [SECOND_BYTE] = 0x1B;    // RTNA [4:0],
                                      // Fosc [hz], 70 [hz].

    spiLcdHw.SendCommand          (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <TWO_BYTES> (SpiHw::EFlag::eDummy, SpiHw::EMode::eData, msg.Data);
}

void ILI9341::sendGammaSet (void)
{
    SpiHw::Msg <ONE_BYTE> msg;
    msg.Cmd               = 0x26;
    msg.Data [FIRST_BYTE] = 0x01;    // GC [7:0]

    spiLcdHw.SendCommand         (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <ONE_BYTE> (SpiHw::EFlag::eDummy, SpiHw::EMode::eData, msg.Data);
}

void ILI9341::sendPositiveGammaCorrection (void)
{
    SpiHw::Msg <FIFTEEN_BYTES> msg;
    msg.Cmd                    = 0xE0;
    msg.Data [FIRST_BYTE]      = 0x1F;    // VP63 [3:0]
    msg.Data [SECOND_BYTE]     = 0x1A;    // VP62 [5:0]
    msg.Data [THIRD_BYTE]      = 0x18;    // VP61 [5:0]
    msg.Data [FOURTH_BYTE]     = 0x0A;    // VP59 [3:0]
    msg.Data [FIFTH_BYTE]      = 0x0F;    // VP57 [4:0]
    msg.Data [SIXTH_BYTE]      = 0x06;    // VP50 [3:0]
    msg.Data [SEVENTH_BYTE]    = 0x45;    // VP43 [6:0]
    msg.Data [EIGHTH_BYTE]     = 0x87;    // VP27 [7:4], VP36 [3:0]
    msg.Data [NINTH_BYTE]      = 0x32;    // VP20 [6:0]
    msg.Data [TENTH_BYTE]      = 0x0A;    // VP13 [3:0]
    msg.Data [ELEVENTH_BYTE]   = 0x07;    // VP6  [4:0]
    msg.Data [TWELFTH_BYTE]    = 0x02;    // VP4  [3:0]
    msg.Data [THIRTEENTH_BYTE] = 0x07;    // VP2  [5:0]
    msg.Data [FOURTEENTH_BYTE] = 0x05;    // VP1  [5:0]
    msg.Data [FIFTEENTH_BYTE]  = 0x00;    // VP0  [3:0]

    spiLcdHw.SendCommand              (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <FIFTEEN_BYTES> (SpiHw::EFlag::eDummy, SpiHw::EMode::eData, msg.Data);
}

void ILI9341::sendNegativeGammaCorrection (void)
{
    SpiHw::Msg <FIFTEEN_BYTES> msg;
    msg.Cmd                    = 0xE1;
    msg.Data [FIRST_BYTE]      = 0x00;    // VN63 [3:0]
    msg.Data [SECOND_BYTE]     = 0x25;    // VN62 [5:0]
    msg.Data [THIRD_BYTE]      = 0x27;    // VN61 [5:0]
    msg.Data [FOURTH_BYTE]     = 0x05;    // VN59 [3:0]
    msg.Data [FIFTH_BYTE]      = 0x10;    // VN57 [4:0]
    msg.Data [SIXTH_BYTE]      = 0x09;    // VN50 [3:0]
    msg.Data [SEVENTH_BYTE]    = 0x3A;    // VN43 [6:0]
    msg.Data [EIGHTH_BYTE]     = 0x78;    // VN36 [7:4], VN27 [3:0]
    msg.Data [NINTH_BYTE]      = 0x4D;    // VN20 [6:0]
    msg.Data [TENTH_BYTE]      = 0x05;    // VN13 [3:0]
    msg.Data [ELEVENTH_BYTE]   = 0x18;    // VN6  [4:0]
    msg.Data [TWELFTH_BYTE]    = 0x0D;    // VN4  [3:0]
    msg.Data [THIRTEENTH_BYTE] = 0x38;    // VN2  [5:0]
    msg.Data [FOURTEENTH_BYTE] = 0x3A;    // VN1  [5:0]
    msg.Data [FIFTEENTH_BYTE]  = 0x1F;    // VN0  [3:0]

    spiLcdHw.SendCommand              (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <FIFTEEN_BYTES> (SpiHw::EFlag::eDummy, SpiHw::EMode::eData, msg.Data);
}

void ILI9341::sendEntryModeSet (void)
{
    SpiHw::Msg <ONE_BYTE> msg;
    msg.Cmd               = 0xB7;
    msg.Data [FIRST_BYTE] = 0x07;    // 0,
                                     // 0,
                                     // DSTB [3] = 0,
                                     // GON  [2] = 1,
                                     // DTE  [1] = 1,
                                     // GAS  [0] = 1.

    spiLcdHw.SendCommand         (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <ONE_BYTE> (SpiHw::EFlag::eDummy, SpiHw::EMode::eData, msg.Data);
}

void ILI9341::sendDisplayFunctionControl (void)
{
    SpiHw::Msg <FOUR_BYTES> msg;
    msg.Cmd                = 0xB6;
    msg.Data [FIRST_BYTE]  = 0x0A;    // PTG   [3:2], PT [1:0]
    msg.Data [SECOND_BYTE] = 0x82;    // REV   [7] = 1,
                                      // GS    [6] = 0,
                                      // SS    [5] = 0,
                                      // SM    [4] = 0,
                                      // ISC   [3:0]

    msg.Data [THIRD_BYTE]  = 0x27;    // NL    [5:0]
    msg.Data [FOURTH_BYTE] = 0x00;    // PCDIV [5:0]

    spiLcdHw.SendCommand           (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <FOUR_BYTES> (SpiHw::EFlag::eDummy, SpiHw::EMode::eData, msg.Data);
}

void ILI9341::sendSleepOut (void)
{
    SpiHw::Msg <ZERO_BYTES> msg;
    msg.Cmd = 0x11;
    spiLcdHw.SendCommand (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd, msg.Cmd);
    Rtos::GetInstance    ()->DelayInMs (ONE_HUNDRED);
}

void ILI9341::sendDisplayOn (void)
{
    SpiHw::Msg <ZERO_BYTES> msg;
    msg.Cmd = 0x29;
    spiLcdHw.SendCommand (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd, msg.Cmd);
    Rtos::GetInstance    ()->DelayInMs (ONE_HUNDRED);
}

uint32_t ILI9341::receiveGetId (void)
{
    SpiHw::Msg <FOUR_BYTES> msg;
    msg.Cmd = 0x04;
    memset                         (msg.Data, ZERO, FOUR_BYTES);
    spiLcdHw.SendCommand           (SpiHw::EFlag::eDummy, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <FOUR_BYTES> (SpiHw::EFlag::eDummy, SpiHw::EMode::eData, msg.Data);
    return *(uint32_t*)msg.Data;
}

void ILI9341::sendMemoryWrite (const SpiHw::EFlag v_eFlag)
{
    SpiHw::Msg <ZERO_BYTES> msg;
    msg.Cmd = 0x2C;
    spiLcdHw.SendCommand (v_eFlag, SpiHw::EMode::eCmd, msg.Cmd);
}

void ILI9341::sendColumnAddressSet (const SpiHw::EFlag v_eFlag, const uint8_t v_scH, const uint8_t v_scL, const uint8_t v_ecH, const uint8_t v_ecL)
{
    SpiHw::Msg <FOUR_BYTES> msg;
    msg.Cmd                = 0x2A;
    msg.Data [FIRST_BYTE]  = v_scH;    // SC [15:8]
    msg.Data [SECOND_BYTE] = v_scL;    // SC [7:0]
    msg.Data [THIRD_BYTE]  = v_ecH;    // EC [15:8]
    msg.Data [FOURTH_BYTE] = v_ecL;    // EC [7:0]

    spiLcdHw.SendCommand           (v_eFlag, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <FOUR_BYTES> (v_eFlag, SpiHw::EMode::eData, msg.Data);
}

void ILI9341::sendPageAddressSet (const SpiHw::EFlag v_eFlag, const uint8_t v_spH, const uint8_t v_spL, const uint8_t v_epH, const uint8_t v_epL)
{
    SpiHw::Msg <FOUR_BYTES> msg;
    msg.Cmd                = 0x2B;
    msg.Data [FIRST_BYTE]  = v_spH;    // SP [15:8]
    msg.Data [SECOND_BYTE] = v_spL;    // SP [7:0]
    msg.Data [THIRD_BYTE]  = v_epH;    // EP [15:8]
    msg.Data [FOURTH_BYTE] = v_epL;    // EP [7:0]

    spiLcdHw.SendCommand           (v_eFlag, SpiHw::EMode::eCmd , msg.Cmd);
    spiLcdHw.SendData <FOUR_BYTES> (v_eFlag, SpiHw::EMode::eData, msg.Data);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
