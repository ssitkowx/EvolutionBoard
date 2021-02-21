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
        Widget           sendButtonDown;
        Widget           sendButtonUp;
        Widget           backButtonDown;
        Widget           backButtonUp;
        WidgetEdit       edit;

    public:
        explicit ActivityBluetooth (Touch<TouchHw> & v_touch, Draftsman<DraftsmanHw> & v_draftsman, Resources & v_resources);
        ~ActivityBluetooth () { Unsubscribe (); }

        void Process (void) override;
        void Start   (void);
        void Update  (void);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
