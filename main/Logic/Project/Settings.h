#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Settings
{
    public:
        struct Lcd
        {
            static constexpr uint16_t Length              = TWO_HUNDRED_FORTY;
            static constexpr uint16_t Width               = THREE_HUNDRED_TWENTY;
            static constexpr uint16_t MaxLinesPerTransfer = TWELVE;
            static constexpr uint8_t  RectsNumber         = FIFTEEN;
        } Lcd;

        Settings () = default;

        static Settings & GetInstance (void)
        {
            static Settings instance;
            return instance;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
