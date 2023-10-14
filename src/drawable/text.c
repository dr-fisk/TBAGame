#include "drawable/text.h"

Text::Text(const Font cFont, const std::string cText, const int32_t cHeight, const int32_t cWidth)
{
  mFont = cFont;
  mLabel = cText;
  mRasterizer.resize(cText.size());
  // Calculate new positions
  // Get maxcoord positions Update if need to
  // set letters side by side
}