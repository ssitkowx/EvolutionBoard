#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "BitmapHw.h"
#include "DisplayHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Resources final
{
    public:
        enum class EId : uint8_t
        {
            eBackground,
            eTest
        };

        std::array <Bitmap *, TWO> resource;

        explicit Resources (Display<DisplayHw> & v_display);

    private:
	    Display<DisplayHw> & display;

        template <const EId ID>
        void create (const uint16_t * v_data)
        {
            static BitmapHw bitmap (display);
            bitmap.Id                              = static_cast <uint8_t> (ID);
            bitmap.IsButton                        = false;
            bitmap.Dimension.Width                 = v_data  [FIRST_BYTE];
            bitmap.Dimension.Height                = v_data  [SECOND_BYTE];
            bitmap.Data                            = &v_data [THIRD_BYTE];
            resource.at (static_cast<uint8_t>(ID)) = &bitmap;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
