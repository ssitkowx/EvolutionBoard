#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <array>
#include "Utils.h"
#include "Bitmap.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Font final
{
    static constexpr char * MODULE = (char *)"Font";

    public:
        enum class EId : uint8_t
        {
            eZero                 = '0',
            eOne                  = '1',
            eTwo                  = '2',
            eThree                = '3',
            eFour                 = '4',
            eFive                 = '5',
            eSix                  = '6',
            eSeven                = '7',
            eEight                = '8',
            eNine                 = '9',
            eA                    = 'A',
            eB                    = 'B',
            eC                    = 'C',
            eD                    = 'D',
            eE                    = 'E',
            eF                    = 'F',
            eG                    = 'G',
            eH                    = 'H',
            eI                    = 'I',
            eJ                    = 'J',
            eK                    = 'K',
            eL                    = 'L',
            eM                    = 'M',
            eN                    = 'N',
            eO                    = 'O',
            eP                    = 'P',
            eQ                    = 'Q',
            eR                    = 'R',
            eS                    = 'S',
            eT                    = 'T',
            eU                    = 'U',
            eV                    = 'V',
            eW                    = 'W',
            eX                    = 'X',
            eY                    = 'Y',
            eZ                    = 'Z',
            eAx                   = 'a',
            eBx                   = 'b',
            eCx                   = 'c',
            eDx                   = 'd',
            eEx                   = 'e',
            eFx                   = 'f',
            eGx                   = 'g',
            eHx                   = 'h',
            eIx                   = 'i',
            eJx                   = 'j',
            eKx                   = 'k',
            eLx                   = 'l',
            eMx                   = 'm',
            eNx                   = 'n',
            eOx                   = 'o',
            ePx                   = 'p',
            eQx                   = 'q',
            eRx                   = 'r',
            eSx                   = 's',
            eTx                   = 't',
            eUx                   = 'u',
            eVx                   = 'v',
            eWx                   = 'w',
            eXx                   = 'x',
            eYx                   = 'y',
            eZx                   = 'z',

            eAmpersand            = '&',
            eBackslash            = '\\',
            eColon                = ':',
            eComma                = ',',
            eCurlyleftBracket     = '{',
            eCurlyRightBracket    = '}',
            eDash                 = '-',
            eDolar                = '$',
            eDot                  = '.',
            eDoubleQuote          = '"',
            eEquation             = '=',
            eExclamation          = '!',
            eExponent             = '^',
            eHash                 = '#',
            eLowerUnderscore      = '_',
            eMonkey               = '@',
            ePercent              = '%',
            ePlus                 = '+',
            eRoundLeftBracket     = '(',
            eRoundRightBracket    = ')',
            eSemicolon            = ';',
            eSingleQuotation      = '\'',
            eSlash                = '/',
            eSnake                = '~',
            eSpace                = ' ',
            eSquareLeftBracket    = '[',
            eSquareRightBracket   = ']',
            eTriangleLeftBracket  = '<',
            eTriangleRightBracket = '>',
            eQuestion             = '?'
        };

        Font ();
        ~Font () = default;

        constexpr Bitmap & operator[] (const EId v_eId) { return *font.at (static_cast<const uint8_t>(v_eId)); }

    private:
        std::array <Bitmap *, TWO_HUNDRED_FIFTY_FIVE> font;

        template <const EId ID>
        void create (const uint16_t * const v_data)
        {
            static_assert (!(static_cast<uint16_t>(ID) > TWO_HUNDRED_FIFTY_FIVE), "Font ID outside boundary: ID > 255");

            static Bitmap bitmap;
            bitmap.Id                          = static_cast <uint8_t> (ID);
            bitmap.Dimension.Width             = v_data  [FIRST_BYTE];
            bitmap.Dimension.Height            = v_data  [SECOND_BYTE];
            bitmap.Data                        = &v_data [THIRD_BYTE];
            font.at (static_cast<uint8_t>(ID)) = &bitmap;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
