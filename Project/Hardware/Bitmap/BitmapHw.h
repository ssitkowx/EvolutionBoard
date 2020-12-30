#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Bitmap.h"
#include "DisplayHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class BitmapHw final : public Bitmap
{
    public:
        enum class EId : uint8_t
        {
            // font
            eNum0 = '0',
            eNum1 = '1',
            eNum2 = '2',
            eNum3 = '3',
            eNum4 = '4',
            eNum5 = '5',
            eNum6 = '6',
            eNum7 = '7',
            eNum8 = '8',
            eNum9 = '9',

            eA    = 'A',
            eB    = 'B',
            eC    = 'C',
            eD    = 'D',
            eE    = 'E',
            eF    = 'F',
            eG    = 'G',
            eH    = 'H',
            eI    = 'I',
            eJ    = 'J',
            eK    = 'K',
            eL    = 'L',
            eM    = 'M',
            eN    = 'N',
            eO    = 'O',
            eP    = 'P',
            eQ    = 'Q',
            eR    = 'R',
            eS    = 'S',
            eT    = 'T',
            eU    = 'U',
            eV    = 'V',
            eW    = 'W',
            eX    = 'X',
            eY    = 'Y',
            eZ    = 'Z',
            eAx   = 'a',
            eBx   = 'b',
            eCx   = 'c',
            eDx   = 'd',
            eEx   = 'e',
            eFx   = 'f',
            eGx   = 'g',
            eHx   = 'h',
            eIx   = 'i',
            eJx   = 'j',
            eKx   = 'k',
            eLx   = 'l',
            eMx   = 'm',
            eNx   = 'n',
            eOx   = 'o',
            ePx   = 'p',
            eQx   = 'q',
            eRx   = 'r',
            eSx   = 's',
            eTx   = 't',
            eUx   = 'u',
            eVx   = 'v',
            eWx   = 'w',
            eXx   = 'x',
            eYx   = 'x',
            eZx   = 'z',

            eKeyNum0Up,
            eKeyNum0Down,
            eKeyNum1Up,
            eKeyNum1Down,
            eKeyNum2Up,
            eKeyNum2Down,
            eKeyNum3Up,
            eKeyNum3Down,
            eKeyNum4Up,
            eKeyNum4Down,
            eKeyNum5Up,
            eKeyNum5Down,
            eKeyNum6Up,
            eKeyNum6Down,
            eKeyNum7Up,
            eKeyNum7Down,
            eKeyNum8Up,
            eKeyNum8Down,
            eKeyNum9Up,
            eKeyNum9Down,

            eBackground
        };

        explicit BitmapHw (Display<DisplayHw> & v_display);
        void     Redraw   (const uint8_t v_id, const Rectangle::Coordinates & v_coordinates);

    private:
        Display<DisplayHw> & display;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
