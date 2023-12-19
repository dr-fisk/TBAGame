#include "drawable/text.h"
#include "drawable/rectangle.h"

Text::Text(const Font& crFont, const std::string& crText, const int32_t cHeight, const int32_t cWidth)
{
  mFont = crFont;
  mText = crText;

  //Replace with paramters
  mVertexes.resize(mText.size());
  Vector2<int32_t> dim(0,0);
  Vector2<int32_t> prev_dim(0,0);

  for(size_t i = 0; i < mText.size(); i ++)
  {
    dim = mFont.getCharacterDimensions(mText[i]);
    std::cout << dim;
    // std::cout << mFont.getYBearing(mText[i]) << std::endl;
    // this breaks gotta keep track of previous topleft location too
    mVertexes[i] = Rect(100 + prev_dim.mX, 100, dim.mY,dim.mX, lg::Black).getVertex()[0];
    prev_dim.mX += dim.mX + 1;
  }
}

std::vector<Vertex> Text::getVertex()
{
  return mVertexes;
}