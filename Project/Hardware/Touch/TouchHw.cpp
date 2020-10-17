///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include "Timer.h"
#include "Utils.h"
#include "TouchHw.h"
#include "LoggerHw.h"
#include "Settings.h"
#include "Rectangle.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Rectangle::Coordinates TouchHw::getCoordinates (void)
{
    uint8_t  xPos = (getPos (createXPosCmd ()) - coefficient.Constant) * coefficient.Width;
    uint16_t yPos = (getPos (createYPosCmd ()) - coefficient.Constant) * coefficient.Length;

    return { xPos, yPos };
}

uint16_t TouchHw::getPos (uint8_t v_cmd)
{
    SpiHw::Msg <ONE_BYTE> msg;
    msg.Cmd = v_cmd;

    memset                           (msg.Data, ZERO, ONE_BYTE);
    spiTouchHw.SendCommand           (SpiHw::EFlag::eDummy , SpiHw::EMode::eCmd , msg.Cmd);
    spiTouchHw.ReceiveData<ONE_BYTE> (SpiHw::EFlag::eRxData, SpiHw::EMode::eData, msg.Data);
    return msg.Data [FIRST_BYTE];
}

uint8_t TouchHw::createXPosCmd (void)
{
    uint8_t command = (static_cast<uint8_t>(EControl::eStart) +
                       static_cast<uint8_t>(EControl::eA2)    +
                       static_cast<uint8_t>(EControl::eA0)    +
                       static_cast<uint8_t>(EControl::eMode)  +
                       static_cast<uint8_t>(EControl::ePd1)   +
                       static_cast<uint8_t>(EControl::ePd0));
    return command;
}

uint8_t TouchHw::createYPosCmd (void)
{
    uint8_t command = (static_cast<uint8_t>(EControl::eStart) +
                       static_cast<uint8_t>(EControl::eA0)    +
                       static_cast<uint8_t>(EControl::eMode)  +
                       static_cast<uint8_t>(EControl::ePd1)   +
                       static_cast<uint8_t>(EControl::ePd0));

    return command;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
