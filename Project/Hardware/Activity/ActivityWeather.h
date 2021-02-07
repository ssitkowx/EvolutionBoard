#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Widget.h"
#include "TouchHw.h"
#include "Activity.h"
#include "DraftsmanHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class ActivityWeather final : public Activity
{
    static constexpr char * MODULE = (char *)"WeatherActivity";

    private:
        static constexpr std::string_view startText     = "  ?  ";
        static constexpr std::string_view spaces        = "                    ";
        Touch<TouchHw>         &          touch;
        Draftsman<DraftsmanHw> &          draftsman;
        Resources              &          resources;
        uint16_t                          startPosX     = TEN;
        uint16_t                          startPosY     = TEN;
        uint16_t                          startMeasureX = ONE_HUNDRED_TWENTY;
        Widget                            background;
        Widget                            buttonDown;
        Widget                            buttonUp;

    public:
        explicit ActivityWeather (Touch<TouchHw> & v_touch, Draftsman<DraftsmanHw> & v_draftsman, Resources & v_resources);
        ~ActivityWeather () { Unsubscribe (); }

        void Process (void) override;
        void Start   (void);
        void Update  (void);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
