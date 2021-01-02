#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static const uint16_t Q [] = 
{ 
    0x002c, 0x0037, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdfff, 0xbad6, 0x55ad, 0x3084, 0xcb5a, 0xc739, 0xe420, 
    0x0842, 0xcb5a, 0x1084, 0x14a5, 0x59ce, 0x7def, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0x7def, 0x34a5, 0x8631, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x8e73, 0x18c6, 0xdfff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x96b5, 0x4529, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x694a, 0x59ce, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9ef7, 0xef7b, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x518c, 0xbef7, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0x9ef7, 0x2c63, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2c63, 0x7def, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbef7, 0x4d6b, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x6e6b, 0x14a5, 0xb6b5, 0xd7bd, 0x96b5, 0xf39c, 0x8e73, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x0c63, 0x9ef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x718c, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0xe420, 0x75ad, 0x7def, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbef7, 0x38c6, 0xeb5a, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xef7b, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x38c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x0c63, 0x5def, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xb6b5, 0x8310, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0xb6b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0x9ef7, 0xc739, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x0c63, 0x9ef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9ad6, 0xe420, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2421, 0x7def, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x34a5, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x8631, 0x5def, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0x59ce, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xd39c, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9ef7, 0xe420, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xd7bd, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0x9294, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x8310, 0x7def, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0x96b5, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2842, 0xdfff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x7def, 0xc318, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x8a52, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xd7bd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd39c, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0xcb5a, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xfbde, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x7def, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdbde, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x3ce7, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x96b5, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x6e6b, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xe739, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x18c6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xcf7b, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xb6b5, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x7294, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xb294, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe420, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x9ad6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd7bd, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2d63, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x5def, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x5def, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9ad6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x8310, 0xdfff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbad6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xc318, 0xdfff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x9ef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0x59ce, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x494a, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9ef7, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x3ce7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd7bd, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0xec62, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdfff, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0xdbde, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xb6b5, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x8e73, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xbad6, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x75ad, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xef7b, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x9ad6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0x96b5, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xae73, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdfff, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xbad6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xb6b5, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2c63, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbef7, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0xfbde, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x694a, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x7def, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x1ce7, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x79ce, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xe420, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0x3ce7, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x5def, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xfbde, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x7def, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9ad6, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xdfff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9ef7, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0xbad6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xb6b5, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x494a, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xc739, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0xd7bd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9294, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xcf7b, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x518c, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xef7b, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0x694a, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x55ad, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xd7bd, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x8310, 0x9ef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xfbde, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x9ad6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x3ce7, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x59ce, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x55ad, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x9ef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xcb5a, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x4d6b, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbef7, 0x2842, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xcf7b, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd7bd, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x9ad6, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0x96b5, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x38c6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0x9ef7, 0xe420, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x6e6b, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x7def, 0x6529, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x6529, 0xbef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0x34a5, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xd7bd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xef7b, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x75ad, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9ef7, 0x8631, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x8310, 0x9ad6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xb294, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xc739, 0xbef7, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x18c6, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0xe420, 0x59ce, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x7def, 0xf07b, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x38c6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x1084, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x518c, 0x1ce7, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x7def, 0x75ad, 0x8631, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x9294, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xbef7, 0xcb5a, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xec62, 0xf39c, 0xb6b5, 0xd7bd, 
    0x96b5, 0xd39c, 0x0c63, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x8e73, 0xbef7, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x5def, 
    0xaa52, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x6e6b, 0xbef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x7def, 0x6d6b, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x9294, 0xbef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdfff, 0x55ad, 0xc318, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x96b5, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x5def, 0xf39c, 0x4529, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2d63, 0xbef7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbef7, 0x9ad6, 0x34a5, 0x1084, 0xaa52, 0xa731, 0x8310, 0x4529, 0x694a, 0xcf7b, 0x8e73, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xeb5a, 0x3ce7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9ef7, 0x494a, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0xc318, 0x34a5, 0x7def, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbad6, 0xc318, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0xcf7b, 0xd7bd, 0xdbde, 0x5def, 0xdfff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9ad6, 0xe420, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xdbde, 0x8a52, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 
    0x2208, 0x2208, 0x2208, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbef7, 
    0xd39c, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x5def, 0xf39c, 0xe420, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbef7, 0x59ce, 0x718c, 0xa731, 0x2208, 
    0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0x2208, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x5def, 0x79ce, 0x96b5, 0xf39c, 0x1084, 
    0x2c63, 0xaa52, 0x0842, 0xffff, 
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////