///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "SpiHw.h"
#include "RtosHw.h"
#include <stdint.h>
#include "GpioHw.h"
#include "Logger.h"
#include "LoggerHw.h"
#include "DisplayHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

extern "C" void MainCppHw (void)
{
    uint16_t xPos   = 0;
    uint16_t yPos   = 0;
    uint16_t width  = 20;
    uint16_t length = 20;

    //printf("Free heap size: %d\n", esp_get_free_heap_size ());
    static LoggerHw loggerHw;
    SET_LOGGER_INST(&loggerHw);

    static RtosHw RtosHw;
    SET_RTOS_INST(&RtosHw);

    GpioHw    gpioHw;
    SpiHw     spiHw;
    DisplayHw display (gpioHw, spiHw);

    while (1)
    {
       xPos = 0;
       yPos = 0;
       display.DrawRect (xPos, yPos, width, length, 0x80);
       xPos+=20;
       yPos+=20;
       display.DrawRect (xPos, yPos, width, length, 0x40);
       xPos+=20;
       yPos+=20;
       display.DrawRect (xPos, yPos, width, length, 0x20);
       xPos+=20;
       yPos+=20;
       display.DrawRect (xPos, yPos, width, length, 0x10);

       xPos+=20;
       yPos+=20;
       display.DrawRect (xPos, yPos, width, length, 0x08);
       xPos+=20;
       yPos+=20;
       display.DrawRect (xPos, yPos, width, length, 0x04);
       xPos+=20;
       yPos+=20;
       display.DrawRect (xPos, yPos, width, length, 0x02);
       xPos+=20;
       yPos+=20;
       display.DrawRect (xPos, yPos, width, length, 0x01);
      // DrawRect (spi, xPos + 10, yPos + 10, length - 20, width - 20, 0x3333);
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
