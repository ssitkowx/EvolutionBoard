#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Spi.h"
#include "Touch.h"
#include <stdint.h>
#include "SpiTouchHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class TouchHw final : public Touch
{
    static constexpr char * MODULE = (char *)"TouchHw";

    enum class EControl : uint8_t
    {
        eStart = (ONE << SEVEN_BITS),
        eA2    = (ONE << SIX_BITS),
        eA1    = (ONE << FIVE_BITS),
        eA0    = (ONE << FOUR_BITS),
        eMode  = (ONE << THREE_BITS),
        eSer   = (ONE << TWO_BITS),
        ePd1   = (ONE << ONE_BIT),
        ePd0   = ONE,
    };

    public:
        TouchHw () = default;
        ~TouchHw () = default;

        static void        WaitForTouch   (void);

        void               Process        (void)          override;
        bool               IsTouched      (void)          override;
        Touch::Coordinates GetCoordinates (void)          override;

    protected:
        uint16_t           getPos         (EAxis v_eAxis) override;

    private:
        SpiTouchHw spiTouchHw;

        uint8_t createXPosCommand (void);
        uint8_t createYPosCommand (void);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
