#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <array>
#include "Font.h"
#include "ButtonsHw.h"
#include "Resources.h"
#include "DraftsmanHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class PresentationActivity
{
    public:
        static constexpr char * MODULE = (char *)"PresentationActivity";

        explicit PresentationActivity (Draftsman<DraftsmanHw> & v_display,
                                       Button<ButtonsHw>      & v_button,
                                       Resources              & v_resources);

        ~PresentationActivity () = default;
		
		void Process (void);
		void Update  (void);

    private:
		Draftsman<DraftsmanHw> & draftsman;
        Button   <ButtonsHw>   & button;
        Resources              & resources;

        static constexpr         std::string_view startText = "  ?  ";
        static constexpr         std::string_view spaces    = "                    ";
        uint16_t                 startPosX                  = TEN;
        uint16_t                 startPosY                  = TEN;
        uint16_t                 startMeasureX              = ONE_HUNDRED_TWENTY;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
