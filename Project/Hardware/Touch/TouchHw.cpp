///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include "Utils.h"
#include "TouchHw.h"
#include "LoggerHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void TouchHw::WaitForTouch (void)
{
    Rtos::GetInstance ()->GiveSemaphoreFromISR ("GiveTouchUpdateSemaphoreFromISR");
}

void TouchHw::Process (void)
{
    if (IsTouched () == true)
    {
        Touch::Coordinates coordinates = GetCoordinates ();
        LOGD (MODULE, "X  position %u", coordinates.X);
        LOGI (MODULE, "Y  position %u", coordinates.Y);
        Rtos::GetInstance ()->Delay (1000);
    }
}

bool               TouchHw::IsTouched      (void) { return Rtos::GetInstance ()->TakeSemaphore ("TakeTouchUpdateSemaphore"); }
Touch::Coordinates TouchHw::GetCoordinates (void) { return { getPos (EAxis::eX), getPos (EAxis::eY) }; }

uint16_t TouchHw::getPos (EAxis v_eAxis)
{
    SpiTouchHw::Msg <ONE_BYTE> msg;

    if      (v_eAxis == EAxis::eX) { msg.Cmd = createXPosCommand (); }
    else if (v_eAxis == EAxis::eY) { msg.Cmd = createYPosCommand (); }
    else                           { LOGE (MODULE, "Unknown axis: %u", static_cast<uint8_t> (v_eAxis)); }

    memset                            (msg.Data, ZERO, ONE_BYTE);
    spiTouchHw.sendCommand            (SpiTouchHw::EFlag::eDummy , SpiTouchHw::EMode::eCmd , msg.Cmd);
    spiTouchHw.receiveData <ONE_BYTE> (SpiTouchHw::EFlag::eRxData, SpiTouchHw::EMode::eData, msg.Data);

    return msg.Data [FIRST_BYTE];
}

uint8_t TouchHw::createXPosCommand (void)
{
    uint8_t command = (static_cast<uint8_t>(EControl::eStart) +
                       static_cast<uint8_t>(EControl::eMode)  +
                       static_cast<uint8_t>(EControl::eA2)    +
                       static_cast<uint8_t>(EControl::eA0)    +
                       static_cast<uint8_t>(EControl::ePd1)   +
                       static_cast<uint8_t>(EControl::ePd0));
    return command;
}

uint8_t TouchHw::createYPosCommand (void)
{
    uint8_t command = (static_cast<uint8_t>(EControl::eStart) +
                       static_cast<uint8_t>(EControl::eMode)  +
                       static_cast<uint8_t>(EControl::eA0)    +
                       static_cast<uint8_t>(EControl::ePd1)   +
                       static_cast<uint8_t>(EControl::ePd0));

    return command;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
