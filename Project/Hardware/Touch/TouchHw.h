#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include "Touch.h"
#include <stdint.h>
#include "TimerHw.h"
#include "SpiTouchHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class TouchHw final : public Touch<TouchHw>
{
    static constexpr char * MODULE = (char *)"TouchHw";
    friend Touch<TouchHw>;

    public:
        struct Coefficients
        {
            uint8_t Constant;
            double  Width;
            double  Length;
        };

        explicit TouchHw (const Coefficients           v_coefficient,
                          const Touch<TouchHw>::Config v_touchConfig,
                          SpiTouchHw             & v_spiTouchHw) : Touch<TouchHw> (v_touchConfig),
                                                                   coefficient    (v_coefficient),
                                                                   spiTouchHw     (v_spiTouchHw)
        {  }

        ~TouchHw () = default;

    protected:
        Rectangle::Coordinates getCoordinates (void);
        uint16_t               getPos         (uint8_t v_cmd);
        bool                   isTouched      (void) { return Rtos::GetInstance ()->TakeSemaphore ("TakeTouchSemaphore"); }

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
        SpiTouchHw &       spiTouchHw;

        uint8_t createXPosCmd (void) const
        {
            uint8_t command = (static_cast<uint8_t>(EControl::eStart) +
                               static_cast<uint8_t>(EControl::eA2)    +
                               static_cast<uint8_t>(EControl::eA0)    +
                               static_cast<uint8_t>(EControl::eMode)  +
                               static_cast<uint8_t>(EControl::ePd1)   +
                               static_cast<uint8_t>(EControl::ePd0));
            return command;
        }

        uint8_t createYPosCmd (void) const
        {
            uint8_t command = (static_cast<uint8_t>(EControl::eStart) +
                               static_cast<uint8_t>(EControl::eA0)    +
                               static_cast<uint8_t>(EControl::eMode)  +
                               static_cast<uint8_t>(EControl::ePd1)   +
                               static_cast<uint8_t>(EControl::ePd0));

            return command;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
