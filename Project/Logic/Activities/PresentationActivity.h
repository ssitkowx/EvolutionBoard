#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <array>
#include "Keyboard.h"
#include "DisplayHw.h"
#include "FontImages.h"
#include "background.h"
#include "PresentationActivity.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class PresentationActivity
{
    public:
        static constexpr char * MODULE = (char *)"PresentationActivity";
 
        PresentationActivity (Display<DisplayHw> & v_display, Keyboard & v_keyboard) : display (v_display), keyboard (v_keyboard)
        {
            // numbers
            Create <BitmapHw::EId::eBackground> (background);
            Create <BitmapHw::EId::eNum0>       (Num0);
            Create <BitmapHw::EId::eNum1>       (Num1);
            Create <BitmapHw::EId::eNum2>       (Num2);
            Create <BitmapHw::EId::eNum3>       (Num3);
            Create <BitmapHw::EId::eNum4>       (Num4);
            Create <BitmapHw::EId::eNum5>       (Num5);
            Create <BitmapHw::EId::eNum6>       (Num6);
            Create <BitmapHw::EId::eNum7>       (Num7);
            Create <BitmapHw::EId::eNum8>       (Num8);
            Create <BitmapHw::EId::eNum9>       (Num9);

            // letters
            Create <BitmapHw::EId::eA>          (A);
            Create <BitmapHw::EId::eB>          (B);
            Create <BitmapHw::EId::eC>          (C);
            Create <BitmapHw::EId::eD>          (D);
            Create <BitmapHw::EId::eE>          (E);
            Create <BitmapHw::EId::eF>          (F);
            Create <BitmapHw::EId::eG>          (G);
            Create <BitmapHw::EId::eH>          (H);
            Create <BitmapHw::EId::eI>          (I);
            Create <BitmapHw::EId::eJ>          (J);
            Create <BitmapHw::EId::eK>          (K);
            Create <BitmapHw::EId::eL>          (L);
            Create <BitmapHw::EId::eM>          (M);
            Create <BitmapHw::EId::eN>          (N);
            Create <BitmapHw::EId::eO>          (O);
            Create <BitmapHw::EId::eP>          (P);
            Create <BitmapHw::EId::eR>          (R);
            Create <BitmapHw::EId::eS>          (S);
            Create <BitmapHw::EId::eT>          (T);
            Create <BitmapHw::EId::eU>          (U);
            Create <BitmapHw::EId::eV>          (K);
            Create <BitmapHw::EId::eW>          (W);
            Create <BitmapHw::EId::eX>          (X);
            Create <BitmapHw::EId::eY>          (Y);
            Create <BitmapHw::EId::eZ>          (Z);
            Create <BitmapHw::EId::eP>          (P);
            Create <BitmapHw::EId::eR>          (R);
            Create <BitmapHw::EId::eS>          (S);
            Create <BitmapHw::EId::eT>          (T);
            Create <BitmapHw::EId::eU>          (U);
            Create <BitmapHw::EId::eAx>         (ax);
            Create <BitmapHw::EId::eBx>         (bx);
            Create <BitmapHw::EId::eCx>         (cx);
            Create <BitmapHw::EId::eDx>         (dx);
            Create <BitmapHw::EId::eEx>         (ex);
            Create <BitmapHw::EId::eFx>         (fx);
            Create <BitmapHw::EId::eGx>         (gx);
            Create <BitmapHw::EId::eHx>         (hx);
            Create <BitmapHw::EId::eIx>         (ix);
            Create <BitmapHw::EId::eJx>         (jx);
            Create <BitmapHw::EId::eKx>         (kx);
            Create <BitmapHw::EId::eLx>         (lx);
            Create <BitmapHw::EId::eMx>         (mx);
            Create <BitmapHw::EId::eNx>         (nx);
            Create <BitmapHw::EId::eOx>         (ox);
            Create <BitmapHw::EId::ePx>         (px);
            Create <BitmapHw::EId::eRx>         (rx);
            Create <BitmapHw::EId::eSx>         (sx);
            Create <BitmapHw::EId::eTx>         (tx);
            Create <BitmapHw::EId::eUx>         (ux);
            Create <BitmapHw::EId::eVx>         (kx);
            Create <BitmapHw::EId::eWx>         (wx);
            Create <BitmapHw::EId::eXx>         (xx);
            Create <BitmapHw::EId::eYx>         (yx);
            Create <BitmapHw::EId::eZx>         (zx);
            Create <BitmapHw::EId::ePx>         (px);
            Create <BitmapHw::EId::eRx>         (rx);
            Create <BitmapHw::EId::eSx>         (sx);
            Create <BitmapHw::EId::eTx>         (tx);
            Create <BitmapHw::EId::eUx>         (ux);
        }

        template <const BitmapHw::EId ID>
        void Create (const uint16_t * v_data)
        {
            static_assert (!(static_cast<uint16_t>(ID) > TWO_HUNDRED_FIFTY_FIVE), "Font ID outside boundary: ID > 255");

            static BitmapHw bitmap (display);
            bitmap.Id                       = static_cast <uint8_t> (ID);
            bitmap.IsButton                 = true;
            bitmap.Coordinate.X             = ZERO;
            bitmap.Coordinate.Y             = ZERO;
            bitmap.Dimension.Width          = v_data  [FIRST_BYTE];
            bitmap.Dimension.Height         = v_data  [SECOND_BYTE];
            bitmap.Data                     = &v_data [THIRD_BYTE];
            font [static_cast<uint8_t>(ID)] = &bitmap;
        }

        ~PresentationActivity () = default;
		
		void Process (void);

    private:
		uint16_t                                      fontNumber = ZERO;
        Display<DisplayHw> &                          display;
        Keyboard           &                          keyboard;
        std::array <Bitmap *, TWO_HUNDRED_FIFTY_FIVE> font;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
