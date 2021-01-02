#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "BitmapHw.h"
#include "DisplayHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Font final
{
    public:
        explicit Font (Display<DisplayHw> & v_display);
		
        enum class EId : uint8_t
        {
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
        };

        std::array <Bitmap *, TWO_HUNDRED_FIFTY_FIVE> font;

    private:
	    Display<DisplayHw> & display;

        template <const EId ID>
        void create (const uint16_t * v_data)
        {
            static_assert (!(static_cast<uint16_t>(ID) > TWO_HUNDRED_FIFTY_FIVE), "Font ID outside boundary: ID > 255");

            static BitmapHw bitmap (display);
            bitmap.Id                          = static_cast <uint8_t> (ID);
            bitmap.IsButton                    = false;
            bitmap.Dimension.Width             = v_data  [FIRST_BYTE];
            bitmap.Dimension.Height            = v_data  [SECOND_BYTE];
            bitmap.Data                        = &v_data [THIRD_BYTE];
            font.at (static_cast<uint8_t>(ID)) = &bitmap;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
