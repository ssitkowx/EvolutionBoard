///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "WidgetEdit.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void WidgetEdit::Draw (void)
{
    Widget::Draw (Id, Coordinate);

    const Bitmap & letterWithMinWidth = resources [Font::EId::eLx];
    const Bitmap & letterWithMaxWidth = resources [Font::EId::eW];
    const uint8_t  avrLetterWidth     = (letterWithMaxWidth.Dimension.Width + letterWithMinWidth.Dimension.Width) * 0.5;
    const uint8_t  editMaxLines       = Dimension.Height / letterWithMinWidth.Dimension.Height;
    double         maxLines           = Text.size () * avrLetterWidth / static_cast<double> (Dimension.Width);

    if ((maxLines - static_cast <uint8_t> (maxLines)) > ZERO) { maxLines = static_cast <uint8_t> (maxLines) + ONE; }
    if (maxLines > editMaxLines)                              { maxLines = editMaxLines; }

    uint16_t charsNum = Dimension.Width / avrLetterWidth;
    for (uint8_t lineNum = ZERO; lineNum < maxLines; lineNum++)
    {
        draftsman.DrawText (Text.substr (lineNum * charsNum, charsNum), { Coordinate.X, static_cast <uint16_t>(Coordinate.Y + lineNum * letterWithMinWidth.Dimension.Height) });
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
