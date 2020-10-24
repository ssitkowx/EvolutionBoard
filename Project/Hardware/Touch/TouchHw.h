#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Touch.h"
#include <stdint.h>
#include "TimerHw.h"
#include "Display.h"
#include "Rectangle.h"
#include "SpiTouchHw.h"
#include "NumericKeyboard.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class TouchHw final : public Touch
{
    static constexpr char * MODULE = (char *)"TouchHw";

    public:
        struct Coefficients
        {
            uint8_t Constant;
            uint8_t Width;
            double  Length;
        };

        explicit TouchHw (TimerHw::Config v_timerConfig, Coefficients v_coefficient,
                          Touch::Config   v_touchConfig, Display &    v_display) : Touch       (v_touchConfig),
                                                                                   coefficient (v_coefficient),
                                                                                   timerHw     (v_timerConfig),
                                                                                   display     (v_display)

        {  }

        ~TouchHw () = default;

    protected:
        Rectangle::Coordinates getCoordinates (void)          override;
        uint16_t               getPos         (uint8_t v_cmd) override;

        virtual bool           isTouched      (void)          override { return Rtos::GetInstance ()->TakeSemaphore ("TakeTouchSemaphore"); }

    private:
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

        const Coefficients coefficient;
        TimerHw            timerHw;
        SpiTouchHw         spiTouchHw;
        Display &          display;

        uint8_t createXPosCmd (void);
        uint8_t createYPosCmd (void);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
