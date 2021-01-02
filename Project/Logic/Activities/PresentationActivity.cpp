///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "BitmapHw.h"
#include "SystemEvents.h"
#include "PresentationActivity.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

PresentationActivity::PresentationActivity (Display<DisplayHw> & v_display,
                                            Keyboard           & v_keyboard,
                                            Font               & v_font,
                                            Resources          & v_resources) : display   (v_display),
                                                                                keyboard  (v_keyboard),
                                                                                font      (v_font),
                                                                                resources (v_resources)
{
    v_keyboard.Redraw ();
}

void PresentationActivity::Process (void)
{
    keyboard.Process ();
    if (SystemEvents::GetInstance ().CircBuf.IsEmpty () == false)
    {
        uint16_t eventId = SystemEvents::GetInstance ().CircBuf.Remove ();
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
