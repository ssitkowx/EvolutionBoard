#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "Widget.h"
#include "TouchHw.h"
#include "Activity.h"
#include "WidgetEdit.h"
#include "DraftsmanHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class ActivityBluetooth final : public Activity
{
    static constexpr char * MODULE = (char *)"ActivityBluetooth";

    private:
        Touch<TouchHw> & touch;
        Resources      & resources;
        Widget           background;
        Widget           aButtonDown;
        Widget           aButtonUp;
        Widget           bButtonDown;
        Widget           bButtonUp;
        Widget           sButtonDown;
        Widget           sButtonUp;
        Widget           rButtonDown;
        Widget           rButtonUp;
        Widget           xButtonDown;
        Widget           xButtonUp;
        Widget           zButtonDown;
        Widget           zButtonUp;
        WidgetEdit       edit;

    public:
        explicit ActivityBluetooth (Touch<TouchHw> & v_touch, Draftsman<DraftsmanHw> & v_draftsman, Resources & v_resources);
        ~ActivityBluetooth () { Unsubscribe (); }

        void Process (void)                override;
        void Start   (uint16_t v_actionId) override;
        void Update  (uint16_t v_actionId) override;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
