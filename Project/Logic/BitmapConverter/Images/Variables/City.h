#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static const uint16_t City [] = 
{ 
    0x0026, 0x0014, 
    0x4d10, 0x2d10, 0x0d08, 0x2e10, 0x2e10, 0x0d08, 0x4f10, 0x2e10, 0x4d10, 0x4d10, 0x4d10, 0x2d10, 0x2c08, 0x4c10, 0x6a10, 0x4a10, 
    0x4b10, 0x4c10, 0x2d10, 0x2e10, 0x0f10, 0x0e10, 0x4e10, 0x0c08, 0x4d10, 0x0c08, 0x2d10, 0x4e10, 0x2d10, 0x0d08, 0x2d10, 0x2d10, 
    0x2d10, 0x0c08, 0x2e10, 0x2e10, 0x2e10, 0x2d10, 0x2c08, 0x2d10, 0x4e10, 0x2d10, 0x4d10, 0x4c10, 0x2c10, 0x2c08, 0x2c10, 0x0c08, 
    0x2c08, 0x4e10, 0x4e10, 0x2b08, 0x1ca5, 0x1fce, 0xb87b, 0x2c10, 0x4d10, 0x0d08, 0x2d10, 0x4e18, 0x0c08, 0x4e10, 0x0c08, 0x6d18, 
    0x4e10, 0x0d08, 0x4e10, 0x4d10, 0x0c08, 0x2d10, 0x2d10, 0x2d10, 0x4e10, 0x0d08, 0x0d10, 0x2e10, 0x4d10, 0x4d10, 0x0c08, 0x2c08, 
    0x4a08, 0x8a10, 0x4908, 0x8a10, 0x6b10, 0x4b10, 0x6d10, 0x0d08, 0x2e10, 0x4d10, 0x5fce, 0x5fef, 0x9b9c, 0x6c18, 0x2c10, 0x4c10, 
    0x6b10, 0x0a08, 0x2d10, 0x0d10, 0x4d10, 0x0c08, 0x0d08, 0x2d10, 0x2d10, 0x4e10, 0x2e10, 0x2d10, 0x0e10, 0x2e10, 0x2d10, 0x4d10, 
    0x2d10, 0x0c08, 0x0c08, 0x6d10, 0x4c10, 0x1563, 0x3fc6, 0x1fe7, 0x7ff7, 0x3fe7, 0xbfd6, 0x9a94, 0x2e29, 0x4c10, 0x2d10, 0x4d10, 
    0x5252, 0xd362, 0xb039, 0x4c10, 0x2c10, 0xf56a, 0xfec5, 0x9db5, 0xb241, 0x4e18, 0x2d10, 0x6e18, 0x0d10, 0x2d10, 0x0d08, 0x2d10, 
    0x0d08, 0x2e10, 0x2e10, 0x4e10, 0x0c08, 0x4d10, 0x4d10, 0x4d10, 0x4d10, 0x0a08, 0x1684, 0x3fef, 0x7fef, 0xbfd6, 0x5ece, 0x5ece, 
    0x3fe7, 0x7fef, 0x3ec6, 0x6e31, 0x2c08, 0x0d08, 0x4d10, 0x2c10, 0x4d10, 0x2c08, 0x2b10, 0x188c, 0x3fe7, 0xbed6, 0x114a, 0x2c10, 
    0x2c10, 0x2d10, 0x0e08, 0x2f10, 0x4e18, 0x0d08, 0x2e10, 0x4e10, 0x0d10, 0x2d10, 0x2c10, 0x4c10, 0x2c10, 0x0c08, 0x6c10, 0xf462, 
    0xffde, 0x5fe7, 0x7894, 0x6910, 0x6910, 0x6808, 0xd05a, 0x9fd6, 0x7fef, 0x1ba5, 0x2b08, 0x4d10, 0x2b08, 0x4b10, 0x2c10, 0x4b10, 
    0x4a10, 0x368c, 0x3ee7, 0x1edf, 0x0f42, 0x6b10, 0x4a10, 0x2b10, 0x4c10, 0x2c10, 0x2d10, 0x2d10, 0x2d10, 0x0c08, 0x4b10, 0x4a10, 
    0x8b18, 0x2908, 0x2b10, 0x4c10, 0x2908, 0x9cb5, 0x7fef, 0xddbd, 0x8c18, 0x2d10, 0x2c10, 0x6c10, 0x4a08, 0x7894, 0x5fef, 0x5dce, 
    0x8f39, 0x4a08, 0x5ece, 0x7fef, 0xba9c, 0x104a, 0xdfde, 0x5fef, 0xbff7, 0x9fef, 0x7fef, 0xdfde, 0x7894, 0x3fe7, 0x1fe7, 0x7473, 
    0x2b08, 0x2c08, 0x6c10, 0x556b, 0x1fe7, 0x3fef, 0x3dce, 0x9ff7, 0x7eb5, 0x2a08, 0xac31, 0x3ec6, 0x5fef, 0x588c, 0x2c08, 0x2e10, 
    0x2d10, 0x2c08, 0x4c10, 0x9352, 0xffe6, 0x7fce, 0xd041, 0x6a10, 0x5cc6, 0xbff7, 0xb99c, 0x6d31, 0x778c, 0xbab5, 0x5ee7, 0x3de7, 
    0x38a5, 0x768c, 0x6f4a, 0x5ece, 0xbff7, 0x38a5, 0x2a08, 0x4c10, 0x4a08, 0xfaa4, 0x7fef, 0x9dd6, 0xdcbd, 0x3fef, 0x9fbd, 0x4b10, 
    0x4e4a, 0xdfde, 0x3fe7, 0x9473, 0x6b10, 0x6d10, 0x2c08, 0x2c10, 0x0d08, 0x6d10, 0x2a08, 0x4a08, 0x4d10, 0x4b08, 0x7dce, 0x7fef, 
    0xb99c, 0x4908, 0x4910, 0x1684, 0x5fef, 0xddd6, 0x2f4a, 0x6a10, 0x4910, 0xb894, 0x7fef, 0x9dd6, 0x7031, 0x0c08, 0xeb20, 0x3ec6, 
    0x7fef, 0xf89c, 0x8a10, 0x4b10, 0x0c08, 0x4e10, 0x4e4a, 0xbfd6, 0x3fe7, 0x3263, 0x2a08, 0x2c08, 0x2c08, 0x4d10, 0x2e10, 0x0d08, 
    0x6d18, 0x4d10, 0x2d08, 0x4c10, 0x5ece, 0x9ff7, 0xba9c, 0x4b10, 0x4a08, 0x1784, 0x3fe7, 0xfede, 0x104a, 0x4b10, 0x6c10, 0xb25a, 
    0x1edf, 0x3fe7, 0x366b, 0x4c10, 0x1263, 0x1fe7, 0x1fe7, 0xd262, 0x4b10, 0x2d10, 0x0e10, 0x0e08, 0x6e4a, 0xbfd6, 0x3fe7, 0xd15a, 
    0x2c10, 0x4e10, 0x4d10, 0x0c08, 0x4d10, 0x4d10, 0x0c08, 0x2d10, 0x2e10, 0x6c10, 0x3dc6, 0x5fef, 0x7994, 0x4b10, 0x6a10, 0x1684, 
    0x3fe7, 0xded6, 0x314a, 0x4d10, 0x0d08, 0x6c10, 0xfcbd, 0x7fef, 0xfca4, 0x6910, 0xd79c, 0x9fef, 0x1dc6, 0xeb20, 0x0b08, 0x4d10, 
    0x2e10, 0x2e10, 0x4e4a, 0xbfd6, 0x1fe7, 0xb47b, 0x4c10, 0x2e10, 0x2d10, 0x4e10, 0x4d10, 0x2b08, 0x2b08, 0x6c10, 0x0d08, 0x2b08, 
    0x9ed6, 0x9fef, 0xba9c, 0x4b10, 0x4a10, 0xf57b, 0x7fef, 0xdede, 0x524a, 0x2d10, 0x2e10, 0x2c08, 0x3784, 0x3fe7, 0x7fce, 0xac31, 
    0x1ac6, 0x9fef, 0x7894, 0x4a10, 0x2c10, 0x2d10, 0x2e10, 0x4f10, 0x6d31, 0x9fd6, 0x7fef, 0x768c, 0x4b10, 0x0d08, 0x2e10, 0x0d08, 
    0x4c10, 0xb45a, 0xdfde, 0x5fce, 0x134a, 0x2b08, 0x5cce, 0x7fef, 0xb99c, 0x6a10, 0x4908, 0xf683, 0x7fef, 0xbed6, 0x314a, 0x2c08, 
    0x4d10, 0x4c10, 0xef41, 0x9fd6, 0x5fef, 0x5384, 0x1ddf, 0xffde, 0xd362, 0x0b08, 0x2d10, 0x2d10, 0x0d10, 0x0d08, 0x4a08, 0x7cb5, 
    0x7fef, 0xdabd, 0xcb18, 0x2b08, 0x4c10, 0x6c10, 0x4a10, 0x588c, 0x7fef, 0x1dc6, 0xad18, 0x4b10, 0x7dce, 0xbff7, 0xb894, 0x6a10, 
    0x4a08, 0xf783, 0x5fe7, 0xbed6, 0x514a, 0x6c10, 0x2c08, 0x4c10, 0x6b10, 0x5bad, 0x5fef, 0x5ac6, 0x9fef, 0xdbbd, 0x0a08, 0x2d10, 
    0x2c10, 0x4c10, 0x2c10, 0x2c10, 0x4c10, 0xd462, 0x5fef, 0x5fe7, 0x778c, 0xa910, 0x4910, 0x4808, 0x8f52, 0xbfd6, 0x5fef, 0xb994, 
    0x6c10, 0x6b10, 0x3cc6, 0x9fef, 0x9894, 0x6a10, 0x4b10, 0xd77b, 0x7fef, 0xddd6, 0x9052, 0x2908, 0x4c10, 0x4d10, 0x4b10, 0x7573, 
    0x1fe7, 0x7fef, 0x7fef, 0x368c, 0x6b10, 0x4d10, 0x4b10, 0x2a08, 0x6b10, 0x4a10, 0x2d10, 0x4b10, 0xf583, 0x5fef, 0x7fef, 0x9fd6, 
    0x3ec6, 0x5fce, 0x3fe7, 0x5fef, 0xdebd, 0x6e31, 0x4c10, 0x4b10, 0x5dce, 0x7fef, 0xb99c, 0x4b10, 0x2c08, 0x9352, 0xffde, 0x9fef, 
    0x3ece, 0x7eb5, 0x4c10, 0x2d08, 0x4c10, 0x4e31, 0x9ed6, 0x9ff7, 0xdede, 0x7052, 0x4b10, 0x2c10, 0x7fb5, 0x3fef, 0x7fb5, 0x4a10, 
    0x2d10, 0x2c10, 0x6a10, 0x136b, 0x1ec6, 0x1fe7, 0x7ff7, 0x5fef, 0xbfde, 0x398c, 0x8c18, 0x2b08, 0x4c10, 0x4b10, 0x3fce, 0x5ff7, 
    0x7c9c, 0x4d10, 0x2c10, 0x0a08, 0x5894, 0xdfde, 0x5fef, 0x5fd6, 0xb239, 0x2d10, 0x2b08, 0x4910, 0xd79c, 0x7fef, 0x7bb5, 0x6910, 
    0x4b10, 0x4c10, 0x5fb5, 0x3ff7, 0x5fb5, 0x2b10, 0x0d08, 0x6e18, 0x0b08, 0x4a10, 0x8a18, 0x2808, 0x4910, 0x4a10, 0x4b10, 0x2b08, 
    0x6d18, 0x4d10, 0x4d10, 0x2b10, 0x4b10, 0x4b10, 0x4d10, 0x0c08, 0x6e18, 0x6d18, 0x4b10, 0x4a10, 0x2a08, 0x2b10, 0x2c10, 0x6c10, 
    0x4b10, 0x6d31, 0xbed6, 0x5fef, 0x9573, 0x4b10, 0x2b08, 0x2c10, 0x2c10, 0x2c10, 0x4c10, 0x4c10, 0x0e10, 0x4f18, 0x2d10, 0x2c10, 
    0x4c10, 0x4b10, 0x6b10, 0x4c10, 0x0c08, 0x6e18, 0x0d08, 0x0d08, 0x0d10, 0x4e10, 0x2c10, 0x2c10, 0x4c10, 0x6d18, 0x0c08, 0x2d10, 
    0x4d10, 0x2c10, 0x4c10, 0x4c10, 0x2c10, 0x4a10, 0x4910, 0x368c, 0x1fe7, 0xbfd6, 0xaf39, 0x4c10, 0x2c10, 0x6d18, 0x2c08, 0x2c10, 
    0x2c08, 0x6d18, 0x2f10, 0x0e08, 0x0e10, 0x2d10, 0x2d10, 0x2c10, 0x2c08, 0x0c08, 0x2d10, 0x0d08, 0x0e10, 0x2e10, 0x2e10, 0x2e10, 
    0x2e10, 0x2d10, 0x0b08, 0x2c10, 0x4e10, 0x0d08, 0x4e10, 0x2d10, 0x0c08, 0x2c10, 0x4c10, 0xb77b, 0x7fd6, 0x5fef, 0x7fef, 0x558c, 
    0x6b10, 0x0c08, 0x4d10, 0x0c08, 0x2c10, 0x4d10, 0x2d10, 0x0c08, 
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////