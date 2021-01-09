///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Bitmap.h"
#include "Resources.h"
#include "DraftsmanHw.h"
#include "SystemEvents.h"
#include "PresentationActivity.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

PresentationActivity::PresentationActivity (Draftsman<DraftsmanHw> & v_draftsman,
                                            Button                 & v_button,
                                            Resources              & v_resources) : draftsman (v_draftsman),
                                                                                    button    (v_button),
                                                                                    resources (v_resources)
{
    Bitmap & bitmap = resources [Resources::EId::eBackground];
    draftsman.DrawBitmap (bitmap);
    v_button .Redraw     ();
    draftsman.DrawText   ("FONTTest", { 0, 0 });
}

void PresentationActivity::Process (void)
{
    button.Process ();
    if (SystemEvents::GetInstance ().CircBuf.IsEmpty () == false)
    {
        uint16_t eventId = SystemEvents::GetInstance ().CircBuf.Remove ();
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
