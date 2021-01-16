#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "Bitmap.h"
#include "Button.h"
#include "TouchHw.h"
#include "DraftsmanHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class ButtonsHw final : public Button
{
    static constexpr char * MODULE = (char *)"ButtonHw";

    public:
        struct Configuration
        {
            Bitmap::Coordinates Coordinate;
        } config;

        explicit ButtonsHw (Configuration            v_config,
                            Draftsman<DraftsmanHw> & v_draftsman,
                            Touch<TouchHw>         & v_touch);

        void     Process   (void) override;
        void     Redraw    (void) override;
        void     Redraw    (const uint8_t v_id, const Bitmap::Coordinates & v_coordinates);

        ~ButtonsHw ();

    private:
        enum class EId : uint8_t
        {
            eBleButtonUp,
            eBleButtonDown,
            eWeatherButtonUp,
            eWeatherButtonDown
        };

        template <const EId ID>
        Bitmap & create (const uint16_t * v_data, const uint16_t v_xPos = ZERO, const uint16_t v_yPos = ZERO, bool v_isButton = true)
        {
            static Bitmap bitmap;
            bitmap.Id               = static_cast <uint8_t> (ID);
            bitmap.IsButton         = v_isButton;
            bitmap.Coordinate.X     = v_xPos;
            bitmap.Coordinate.Y     = v_yPos;
            bitmap.Dimension.Width  = v_data  [FIRST_BYTE];
            bitmap.Dimension.Height = v_data  [SECOND_BYTE];
            bitmap.Data             = &v_data [THIRD_BYTE];
            registerBitmap (&bitmap);
            return bitmap;
        }

        Draftsman<DraftsmanHw> & draftsman;
        Touch<TouchHw>         & touch;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
