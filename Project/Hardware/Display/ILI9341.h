#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "SpiLcdHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class ILI9341
{
    private:
        SpiLcdHw & spiLcdHw;

    public:
        ILI9341 (SpiLcdHw & v_spiLcdHw) : spiLcdHw (v_spiLcdHw) { }

        void     SendSoftwareReset           (void);
        uint8_t  ReceiveDisplayPixelFormat   (void);
        void     SendDisplayOff              (void);
        void     SendPowerControl1           (void);
        void     SendPowerControl2           (void);
        void     SendVCOMControl1            (void);
        void     SendVCOMControl2            (void);
        void     SendMemoryAccessControl     (void);
        void     SendPixelFormatSet          (void);
        void     SendFrameRateControl        (void);
        void     SendGammaSet                (void);
        void     SendPositiveGammaCorrection (void);
        void     SendNegativeGammaCorrection (void);
        void     SendEntryModeSet            (void);
        void     SendDisplayFunctionControl  (void);
        void     SendSleepOut                (void);
        void     SendDisplayOn               (void);
        void     SendMemoryWrite             (const SpiHw::EFlag v_eFlag);
        void     SendColumnAddressSet        (const SpiHw::EFlag v_eFlag, const uint8_t v_scH, const uint8_t v_scL,
                                                                          const uint8_t v_ecH, const uint8_t v_ecL);
        void     SendPageAddressSet          (const SpiHw::EFlag v_eFlag, const uint8_t v_spH, const uint8_t v_spL,
                                                                          const uint8_t v_epH, const uint8_t v_epL);
        uint32_t ReceiveGetId                (void);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
