#pragma once

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#define SYSTEM_EVENTS_QUEUE_LEN 10

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include <stdint.h>
#include "CircularBuffer.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


class SystemEvents final
{
    public:
        CircularBuffer <uint8_t, SYSTEM_EVENTS_QUEUE_LEN> CircBuf;

        static SystemEvents & GetInstance (void)
        {
            static SystemEvents instance;
            return instance;
        }

    private:
        SystemEvents () = default;
        ~SystemEvents () = default;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////