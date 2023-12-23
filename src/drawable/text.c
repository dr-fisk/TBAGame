#include "drawable/text.h"
#include "drawable/rectangle.h"

Text::Text(const Font& crFont, const std::string& crText, const int32_t cTop, const int32_t cLeft,
           const int32_t cLineWrap)
{
  mFont = crFont;
  mText = crText;
  mTop = cTop;
  mLeft = cLeft;
  mLineWrap = cLineWrap;

  // mFont.updateFontTextures(12);

  //Replace with paramters
  mVertexes.resize(mText.size());
  gridfitText();
}

void Text::gridfitText()
{
  Vector2<int32_t> dim(0,0);

  int32_t top = mTop;
  int32_t left = mLeft;
  for(size_t i = 0; i < mText.size(); i ++)
  {
    dim = mFont.getCharacterDimensions(mText[i]);

    // Update for more dynamic behavior
    if((0 <= mLineWrap) && (left > mLeft + mLineWrap))
    {
      top += 12 + 2; // replace with top member viriable plus linespace
      left = mLeft;
    }

    mVertexes[i] = Rect(left, top + mFont.getYBearing(mText[i]) + 
    mFont.getYDescent(mText[i]), dim.y - 1,dim.x - 1, lg::Black).getVertex()[0];
    left += dim.x + 1;
  }
}

std::vector<Vertex> Text::getVertex()
{
  return mVertexes;
}