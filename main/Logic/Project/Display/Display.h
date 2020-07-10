#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Display
{
    static constexpr char * MODULE = (char *)"Display";

    public:
        Display          () = default;
        virtual ~Display () = default;

        virtual void DrawRect    (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length, const uint16_t v_color) = 0;
        virtual void DrawText    (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data  , const uint16_t v_len)                            = 0;
        virtual void DrawPicture (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data  , const uint16_t v_len)                            = 0;

};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
