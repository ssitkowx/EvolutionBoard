///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Font.h"
#include "FontImages.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Font::Font (Display<DisplayHw> & v_display) : display (v_display)
{
    create <EId::eNum0> (Num0);
    create <EId::eNum1> (Num1);
    create <EId::eNum2> (Num2);
    create <EId::eNum3> (Num3);
    create <EId::eNum4> (Num4);
    create <EId::eNum5> (Num5);
    create <EId::eNum6> (Num6);
    create <EId::eNum7> (Num7);
    create <EId::eNum8> (Num8);
    create <EId::eNum9> (Num9);
    create <EId::eA>    (A);
    create <EId::eB>    (B);
    create <EId::eC>    (C);
    create <EId::eD>    (D);
    create <EId::eE>    (E);
    create <EId::eF>    (F);
    create <EId::eG>    (G);
    create <EId::eH>    (H);
    create <EId::eI>    (I);
    create <EId::eJ>    (J);
    create <EId::eK>    (K);
    create <EId::eL>    (L);
    create <EId::eM>    (M);
    create <EId::eN>    (N);
    create <EId::eO>    (O);
    create <EId::eP>    (P);
    create <EId::eR>    (R);
    create <EId::eS>    (S);
    create <EId::eT>    (T);
    create <EId::eU>    (U);
    create <EId::eV>    (K);
    create <EId::eW>    (W);
    create <EId::eX>    (X);
    create <EId::eY>    (Y);
    create <EId::eZ>    (Z);
    create <EId::eP>    (P);
    create <EId::eR>    (R);
    create <EId::eS>    (S);
    create <EId::eT>    (T);
    create <EId::eU>    (U);
    create <EId::eAx>   (ax);
    create <EId::eBx>   (bx);
    create <EId::eCx>   (cx);
    create <EId::eDx>   (dx);
    create <EId::eEx>   (ex);
    create <EId::eFx>   (fx);
    create <EId::eGx>   (gx);
    create <EId::eHx>   (hx);
    create <EId::eIx>   (ix);
    create <EId::eJx>   (jx);
    create <EId::eKx>   (kx);
    create <EId::eLx>   (lx);
    create <EId::eMx>   (mx);
    create <EId::eNx>   (nx);
    create <EId::eOx>   (ox);
    create <EId::ePx>   (px);
    create <EId::eRx>   (rx);
    create <EId::eSx>   (sx);
    create <EId::eTx>   (tx);
    create <EId::eUx>   (ux);
    create <EId::eVx>   (kx);
    create <EId::eWx>   (wx);
    create <EId::eXx>   (xx);
    create <EId::eYx>   (yx);
    create <EId::eZx>   (zx);
    create <EId::ePx>   (px);
    create <EId::eRx>   (rx);
    create <EId::eSx>   (sx);
    create <EId::eTx>   (tx);
    create <EId::eUx>   (ux);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
