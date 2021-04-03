#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Widget.h"
#include "TouchHw.h"
#include "Activity.h"
#include "Resources.h"
#include "DraftsmanHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class ActivityWeather final : public Activity
{
    static constexpr char * MODULE = (char *)"WeatherActivity";

    private:
        Touch<TouchHw>         &          touch;
        Draftsman<DraftsmanHw> &          draftsman;
        Resources              &          resources;
        Widget                            background;
        Widget                            bleButtonUp;
        Widget                            bleButtonDown;

    public:
        static constexpr std::string_view Spaces = "               ";

        explicit ActivityWeather (Touch<TouchHw> & v_touch, Draftsman<DraftsmanHw> & v_draftsman, Resources & v_resources);
        ~ActivityWeather () { Unsubscribe (); }

        void Process (void)                      override;
        void Start   (const uint16_t v_actionId) override;
        void Update  (const uint16_t v_actionId) override;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
