#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Font.h"
#include "Utils.h"
#include "Bitmap.h"
#include "LoggerHw.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//#include <optional>
class Resources final
{
    static constexpr char * MODULE = (char *)"Resources";

    public:
        enum class EId : uint8_t
        {
            eCity,
            eSpaces,
            eHumidity,
            ePressure,
            eWindSpeed,
            eBackground,
            eTemperature,
        };

        Resources ();
        ~Resources () = default;

        constexpr Bitmap & operator[] (EId v_eId)       { return *resource.at (static_cast<uint8_t>(v_eId)); }
        constexpr Bitmap & operator[] (Font::EId v_eId) { return font [v_eId]; }

    private:
        Font                       font;
        std::array <Bitmap *, TEN> resource;

        template <const EId ID>
        void create (const uint16_t * v_data)
        {
            static Bitmap bitmap;
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
