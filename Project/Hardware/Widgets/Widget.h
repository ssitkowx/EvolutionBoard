#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "Bitmap.h"
#include "DraftsmanHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Widget : public Bitmap
{
    private:
        Draftsman<DraftsmanHw> & draftsman;

    public:
        bool IsUpdatable = false;

        explicit Widget (Draftsman<DraftsmanHw> & v_draftsman) : draftsman (v_draftsman) {}

        template <const uint16_t ID>
        void Create (const uint16_t * v_data, const uint16_t v_xPos, const uint16_t v_yPos, bool v_isUpdatable = false)
        {
            Id               = static_cast <uint8_t> (ID);
            IsUpdatable      = v_isUpdatable;
            Coordinate.X     = v_xPos;
            Coordinate.Y     = v_yPos;
            Dimension.Width  = v_data  [FIRST_BYTE];
            Dimension.Height = v_data  [SECOND_BYTE];
            Data             = &v_data [THIRD_BYTE];
        }

        void         Draw (void);
        virtual void Draw (const uint16_t v_id, const Bitmap::Coordinates & v_coordinates);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
