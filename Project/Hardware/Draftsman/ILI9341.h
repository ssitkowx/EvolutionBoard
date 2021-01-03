#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Bitmap.h"
#include "SpiLcdHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class ILI9341
{
    static constexpr char * MODULE = (char *)"ILI9341";

    public:
        explicit ILI9341 (SpiLcdHw & v_spiLcdHw);
        void     SendLines                   (const Bitmap & v_bitmap);

    private:
        SpiLcdHw & spiLcdHw;

        void     sendSoftwareReset           (void);
        uint8_t  receiveDisplayPixelFormat   (void);
        void     sendDisplayOff              (void);
        void     sendPowerControl1           (void);
        void     sendPowerControl2           (void);
        void     sendVCOMControl1            (void);
        void     sendVCOMControl2            (void);
        void     sendMemoryAccessControl     (void);
        void     sendPixelFormatSet          (void);
        void     sendFrameRateControl        (void);
        void     sendGammaSet                (void);
        void     sendPositiveGammaCorrection (void);
        void     sendNegativeGammaCorrection (void);
        void     sendEntryModeSet            (void);
        void     sendDisplayFunctionControl  (void);
        void     sendSleepOut                (void);
        void     sendDisplayOn               (void);
        void     sendMemoryWrite             (const SpiHw::EFlag v_eFlag);
        void     sendColumnAddressSet        (const SpiHw::EFlag v_eFlag, const uint8_t v_scH, const uint8_t v_scL,
                                                                          const uint8_t v_ecH, const uint8_t v_ecL);
        void     sendPageAddressSet          (const SpiHw::EFlag v_eFlag, const uint8_t v_spH, const uint8_t v_spL,
                                                                          const uint8_t v_epH, const uint8_t v_epL);
        uint32_t receiveGetId                (void);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
