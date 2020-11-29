#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Keyboard.h"
#include "DisplayHw.h"
#include "BaseWindow.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class BaseWindow
{
    public:
        static constexpr char * MODULE = (char *)"BaseWindow";
 
        BaseWindow (Display<DisplayHw> & v_display, Keyboard & v_keyboard) : display (v_display), keyboard (v_keyboard) {}
        ~BaseWindow () = default;
		
		void Process (void);

    private:
        Display<DisplayHw> & display;
        Keyboard           & keyboard;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////