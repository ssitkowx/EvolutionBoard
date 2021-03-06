#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "Widget.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Activity
{
    protected:
        std::vector <std::reference_wrapper<Widget>> widgets;

    public:
        Activity () = default;
        virtual ~Activity () = default;

        virtual void Process     (void) = 0;
        virtual void Start       (const uint16_t v_actionId = 0);
        virtual void Update      (const uint16_t v_actionId = 0);
        void         Subscribe   (Widget & v_widget) { widgets.emplace_back (v_widget);                   }
        void         Unsubscribe (void)              { while (!widgets.empty ()) { widgets.pop_back (); } }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
