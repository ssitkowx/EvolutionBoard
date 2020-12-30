#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static const uint16_t Nn [] = 
{ 
    0x0020, 0x0048, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xcf7b, 0x2208, 0x2208, 0x2208, 0x2208, 0x0842, 0x9ef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdbde, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x79ce, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xae73, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x9294, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbad6, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x694a, 0xbef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x6e6b, 0x2208, 
    0x2208, 0x2208, 0x2208, 0xbad6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9ad6, 0x2208, 0x2208, 
    0x2208, 0x2208, 0xf39c, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x4d6b, 0x2208, 0x2208, 
    0x2208, 0xcb5a, 0xbef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x79ce, 0x2208, 0x2208, 0x2208, 
    0x2208, 0xfbde, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0c63, 0x2208, 0x2208, 0x2208, 
    0x55ad, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x59ce, 0x2208, 0x2208, 0x2208, 0x2c63, 
    0xdfff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0x3ce7, 0x2208, 0x2208, 0x75ad, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0xdbde, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x494a, 0x9ef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x3084, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xd7bd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xc318, 0x1ce7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xcb5a, 0xbef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x9294, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x38c6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x4529, 0x3ce7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x4d6b, 0xdfff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x14a5, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xeb5a, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x79ce, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xb294, 0x2208, 0x2208, 0x2208, 0x2208, 0xc739, 0x7def, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xbef7, 0x8a52, 0x2208, 0x2208, 0x2208, 0x2208, 0xae73, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xdbde, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x75ad, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0x55ad, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xdbde, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xdfff, 0x4d6b, 0x2208, 0x2208, 0x2208, 0x2208, 0x494a, 
    0x9ef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0x3ce7, 0x2421, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x3084, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xf7bd, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0xd7bd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x3084, 0x2208, 0x2208, 0x2208, 
    0x2208, 0xc318, 0x1ce7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9ef7, 0x0842, 0x2208, 0x2208, 
    0x2208, 0x2208, 0xcb5a, 0xbef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x7ace, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x9294, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd39c, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x18c6, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbef7, 0xcb5a, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x4529, 0x3ce7, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xfbde, 
    0x8310, 0x2208, 0x2208, 0x2208, 0x2208, 0x4d6b, 0xdfff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0x96b5, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x14a5, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xae73, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x79ce, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0x5def, 0x6529, 0x2208, 0x2208, 0x2208, 0x2208, 0xc739, 0x7def, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xae73, 0xf7bd, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0x518c, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x494a, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0x9ef7, 0x494a, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xbad6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x14a5, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdfff, 0x0c63, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x1ce7, 0xc318, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xb6b5, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xcf7b, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x7def, 0xa731, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x59ce, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9294, 0x2208, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbef7, 0x8a52, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdbde, 0x2208, 0x2208, 0x2208, 0xfbde, 
    0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x55ad, 0x2208, 0x2208, 0xfbde, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdfff, 0x4d6b, 0x2208, 0xfbde, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////