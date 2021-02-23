///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Font.h"
#include "LoggerHw.h"
#include "FontImages.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Font::Font ()
{
    LOG                                 (MODULE, "Init.");

    create <EId::eZero                > (zero);
    create <EId::eOne                 > (one);
    create <EId::eTwo                 > (two);
    create <EId::eThree               > (three);
    create <EId::eFour                > (four);
    create <EId::eFive                > (five);
    create <EId::eSix                 > (six);
    create <EId::eSeven               > (seven);
    create <EId::eEight               > (eight);
    create <EId::eNine                > (nine);
    create <EId::eA                   > (A);
    create <EId::eB                   > (B);
    create <EId::eC                   > (C);
    create <EId::eD                   > (D);
    create <EId::eE                   > (E);
    create <EId::eF                   > (F);
    create <EId::eG                   > (G);
    create <EId::eH                   > (H);
    create <EId::eI                   > (I);
    create <EId::eJ                   > (J);
    create <EId::eK                   > (K);
    create <EId::eL                   > (L);
    create <EId::eM                   > (M);
    create <EId::eN                   > (N);
    create <EId::eO                   > (O);
    create <EId::eP                   > (P);
    create <EId::eR                   > (R);
    create <EId::eS                   > (S);
    create <EId::eT                   > (T);
    create <EId::eU                   > (U);
    create <EId::eV                   > (V);
    create <EId::eW                   > (W);
    create <EId::eX                   > (X);
    create <EId::eY                   > (Y);
    create <EId::eZ                   > (Z);
    create <EId::eP                   > (P);
    create <EId::eQ                   > (Q);
    create <EId::eR                   > (R);
    create <EId::eS                   > (S);
    create <EId::eT                   > (T);
    create <EId::eU                   > (U);
    create <EId::eAx                  > (ax);
    create <EId::eBx                  > (bx);
    create <EId::eCx                  > (cx);
    create <EId::eDx                  > (dx);
    create <EId::eEx                  > (ex);
    create <EId::eFx                  > (fx);
    create <EId::eGx                  > (gx);
    create <EId::eHx                  > (hx);
    create <EId::eIx                  > (ix);
    create <EId::eJx                  > (jx);
    create <EId::eKx                  > (kx);
    create <EId::eLx                  > (lx);
    create <EId::eMx                  > (mx);
    create <EId::eNx                  > (nx);
    create <EId::eOx                  > (ox);
    create <EId::ePx                  > (px);
    create <EId::eQx                  > (qx);
    create <EId::eRx                  > (rx);
    create <EId::eSx                  > (sx);
    create <EId::eUx                  > (ux);
    create <EId::eVx                  > (vx);
    create <EId::eWx                  > (wx);
    create <EId::eXx                  > (xx);
    create <EId::eYx                  > (yx);
    create <EId::eZx                  > (zx);
    create <EId::ePx                  > (px);
    create <EId::eRx                  > (rx);
    create <EId::eSx                  > (sx);
    create <EId::eTx                  > (tx);
    create <EId::eUx                  > (ux);

    create <EId::ePlus                > (plus);
    create <EId::eAmpersand           > (ampersand);
    create <EId::eBackslash           > (backslash);
    create <EId::eColon               > (colon);
    create <EId::eComma               > (comma);
    create <EId::eCurlyleftBracket    > (curlyleftbracket);
    create <EId::eCurlyRightBracket   > (curlyrightbracket);
    create <EId::eDash                > (dash);
    create <EId::eComma               > (comma);
    create <EId::eDolar               > (dolar);
    create <EId::eDot                 > (dot);
    create <EId::eDoubleQuote         > (doublequote);
    create <EId::eEquation            > (equation);
    create <EId::eExclamation         > (exclamation);
    create <EId::eHash                > (hash);
    create <EId::eLowerUnderscore     > (lowerunderscore);
    create <EId::eMonkey              > (monkey);
    create <EId::ePercent             > (percent);
    create <EId::eRoundLeftBracket    > (roundleftbracket);
    create <EId::eRoundRightBracket   > (roundrightbracket);
    create <EId::eSemicolon           > (semicolon);
    create <EId::eSingleQuotation     > (singlequotation);
    create <EId::eSlash               > (slash);
    create <EId::eSnake               > (snake);
    create <EId::eSpace               > (space);
    create <EId::eSquareLeftBracket   > (squareleftbracket);
    create <EId::eSquareRightBracket  > (squarerightbracket);
    create <EId::eTriangleLeftBracket > (triangleleftbracket);
    create <EId::eTriangleRightBracket> (trianglerightbracket);
    create <EId::eQuestion            > (question);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
