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
    Bitmap & background = resources [Resources::EId::eBackground];
    draftsman.DrawBitmap (background);

    Bitmap & city         = resources [Resources::EId::eCity];
    city.Coordinate.X     = TEN;
    city.Coordinate.Y     = TEN;
    draftsman.DrawBitmap (city);

    Bitmap & spaces       = resources [Resources::EId::eSpaces];
    spaces.Coordinate.X   = city.Coordinate.X + city.Dimension.Width;
    spaces.Coordinate.Y   = city.Coordinate.Y;
    draftsman.DrawBitmap (spaces);

    Bitmap & humidity     = resources [Resources::EId::eHumidity];
    humidity.Coordinate.X = TEN;
    humidity.Coordinate.Y = city.Coordinate.Y + city.Dimension.Height + FIVE;
    draftsman.DrawBitmap (humidity);

    spaces                = resources [Resources::EId::eSpaces];
    spaces.Coordinate.X   = city.Coordinate.X + city.Dimension.Width;
    spaces.Coordinate.Y   = city.Coordinate.X + city.Dimension.Width;
    draftsman.DrawBitmap (spaces);

    v_button .Redraw     ();
    //draftsman.DrawText   ("FONTTes", { 0, 0 });
}

void PresentationActivity::Process (void)
{
    button.Process ();
    if (SystemEvents::GetInstance ().CircBuf.IsEmpty () == false)
    {
        uint16_t eventId = SystemEvents::GetInstance ().CircBuf.Remove ();
        //LOGI (MODULE, "Event: %d", eventId);
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
