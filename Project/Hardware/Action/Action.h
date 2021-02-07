#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "ActivityWeather.h"
#include "ActivityBluetooth.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Action
{
    static constexpr char * MODULE = (char *)"Action";

    private:
        Draftsman<DraftsmanHw> & draftsman;
        Resources              & resources;
        Activity               * currentActivity = nullptr;
        ActivityWeather          weatherActivity;
        ActivityBluetooth        bluetoothActivity;

    public:
        Action (Touch <TouchHw> & v_touch, Draftsman<DraftsmanHw> & v_draftsman, Resources & v_resources);
        ~Action () = default;

        void Process (void);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////