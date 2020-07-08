#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <memory>
#include <stdio.h>
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Byte number
#define ZERO                        0
#define ONE                         1
#define TWO                         2
#define THREE                       3
#define FOUR                        4
#define FIVE                        5
#define SIX                         6
#define SEVEN                       7
#define EIGHT                       8
#define NINE                        9
#define TEN                         10
#define ELEVEN                      11
#define TWELVE                      12
#define THIRTEEN                    13
#define FOURTEEN                    14
#define FIFTEEN                     15
#define SIXTEEN                     16
#define SEVENTEEN                   17
#define EIGHTEEN                    18
#define NINETEEN                    19
#define TWENTY                      20
#define TWENTY_THREE                23
#define TWENTY_FOUR                 24
#define TWENTY_NINE                 29
#define THIRTY                      30
#define THIRTY_ONE                  31
#define THIRTY_TWO                  32
#define FIFTY                       50
#define SIXTY_FOUR                  64
#define ONE_HUNDRED                 100
#define TWO_HUNDREDS                200
#define ONE_HUNDRED_TWENTY_EIGHT    128
#define TWO_HUNDREDS_TWENTY_FIVE    255
#define THREE_HUNDRED               300
#define THREE_THOUSAND              3000
#define THREE_THOUSAND_SIX_HUNDRED  3600
#define THREE_THOUSAND_NEUN_HUNDRED 3900

#define FIRST_BYTE                  ZERO
#define SECOND_BYTE                 ONE
#define THIRD_BYTE                  TWO
#define FOURTH_BYTE                 THREE
#define FIFTH_BYTE                  FOUR
#define SIXTH_BYTE                  FIVE
#define SEVENTH_BYTE                SIX
#define EIGHTH_BYTE                 SEVEN
#define NINTH_BYTE                  EIGHT
#define TENTH_BYTE                  NINE
#define ELEVENTH_BYTE               TEN
#define TWELFTH_BYTE                ELEVEN
#define THIRTEENTH_BYTE             TWELVE
#define FOURTEENTH_BYTE             THIRTEEN
#define FIFTEENTH_BYTE              FOURTEEN
#define SIXTEENTH_BYTE              FIFTEEN
#define SEVENTEENTH_BYTE            SIXTEEN
#define EIGHTEENTH_BYTE             SEVENTEEN
#define NINETEENTH_BYTE             EIGHTEEN
#define TWENTYTH_BYTE               NINETEEN
#define TWENTYFIRST_BYTE            TWENTY
#define TWENTY_FOURTH_BYTE          TWENTY_THREE
#define THIRTY_BYTES                THIRTY
#define THIRTY_SECOND_BYTE          THIRTY_ONE

#define ZERO_BYTES                  ZERO
#define ONE_BYTE                    ONE
#define TWO_BYTES                   TWO
#define THREE_BYTES                 THREE
#define FOUR_BYTES                  FOUR
#define FIVE_BYTES                  FIVE
#define SIX_BYTES                   SIX
#define SEVEN_BYTES                 SEVEN
#define EIGHT_BYTES                 EIGHT
#define FIFTEEN_BYTES               FIFTEEN
#define EIGHTEEN_BYTES              EIGHTEEN
#define TWENTY_BYTES                TWENTY
#define THIRTY_TWO_BYTES            THIRTY_TWO
#define FIFTY_BYTES                 FIFTY
#define SIXTY_FOUR_BYTES            SIXTY_FOUR

#define ONE_BIT                     ONE
#define TWO_BITS                    TWO
#define THREE_BITS                  THREE
#define FOUR_BITS                   FOUR
#define FIVE_BITS                   FIVE
#define SIX_BITS                    SIX
#define SEVEN_BITS                  SEVEN
#define NINE_BITS                   NINE
#define ELEVEN_BITS                 ELEVEN
#define EIGHTEEN_BITS               EIGHTEEN
#define TWENTY_NINE_BITS            TWENTY_NINE

#define FIRST_BIT                   ONE
#define SECOND_BIT                  TWO
#define THIRD_BIT                   FOUR
#define FOURTH_BIT                  EIGHT
#define FIFTH_BIT                   SIXTEEN
#define SIXTH_BIT                   THIRTY_TWO
#define SEVENTH_BIT                 SIXTY_FOUR
#define EIGHTH_BIT                  ONE_HUNDRED_TWENTY_EIGHT

#define EIGHT_BITS                  EIGHT
#define SIXTEEN_BITS                SIXTEEN
#define TWENTY_FOUR_BITS            TWENTY_FOUR

#define MASK_BIT_POS_0              FIRST_BIT
#define MASK_BIT_POS_1              SECOND_BIT
#define MASK_BIT_POS_2              THIRD_BIT
#define MASK_BIT_POS_3              FOURTH_BIT
#define MASK_BIT_POS_4              FIFTH_BIT
#define MASK_BIT_POS_5              SIXTH_BIT
#define MASK_BIT_POS_6              SEVENTH_BIT
#define MASK_BIT_POS_7              EIGHTH_BIT

#define REQ_BUF_LEN                 ONE_BYTE

#define MASK_LOW_BYTE               0x00FF
#define MASK_HIGH_BYTE              0xFF00

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <class... TArgs>
std::string Format (const std::string & v_format, const TArgs &... v_args)
{
    // Based on https://stackoverflow.com/a/26221725
    // Find buffer size needed, extra space for trailing '\0'

    size_t size = snprintf (nullptr, FIRST_BYTE, v_format.c_str (), v_args...) + ONE_BYTE;
    std::unique_ptr <char []> buf (new char [size]);
    size_t written = snprintf (buf.get (), size, v_format.c_str (), v_args...);
    if (written <= ZERO) { return {}; }
                    
    return std::string (buf.get (), buf.get () + size - ONE_BYTE);     // remove '\0'
}

uint8_t CharToint (const char v_char);
uint8_t HexToInt  (const char v_char [TWO]);

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
