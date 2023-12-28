#include "drawable/text.h"
#include "drawable/rectangle.h"
#include "utility/vertexUtility.h"

//! @brief Text Constructor
//!
//! @param[in]  prFont         Font Object to be used when rendering Text
//! @param[in]  crText         String to be rendered
//! @param[out] prRenderEngine Resource Manager to create Texture Resource
//! @param[in]  cCharSize      Font Size
//! @param[in]  cTop           Top position of Text
//! @param[in]  cLeft          Left Position of Text
//! @param[in]  cLineWrap      Number of pixels before line of texts wraps under
//!
//! @return Text Object 
Text::Text(std::shared_ptr<Font>& prFont, const std::string& crText, std::shared_ptr<RenderEngine>& prRenderEngine,
           std::shared_ptr<BatchBuffer>& prBatch, const uint8_t cCharSize, const int32_t cTop, const int32_t cLeft,
           const int32_t cLineWrap) : Drawable(prBatch)
{
  mpFont = prFont;
  mText = crText;
  mTop = cTop;
  mLeft = cLeft;
  mLineWrap = cLineWrap;
  mCharSize = cCharSize;

  if(!mpFont->hasGlyphsLoaded(mCharSize))
  {
    mpFont->loadGlyphs(mCharSize, prRenderEngine);
  }

  //Replace with paramters
  mVertexes.resize(mText.size());
  mVertexesData.resize(mText.size());

  gridfitText();
}

//! @brief Creates layout of Text
//!
//! @return None
void Text::gridfitText()
{
  Vector2<uint32_t> dim(0,0);

  int32_t top = mTop;
  int32_t left = mLeft;
  TextureResource& temp = getResource();

  for(size_t i = 0; i < mText.size(); i ++)
  {
    dim = mpFont->getCharacterDimensions(mCharSize, mText[i]);

    // Update for more dynamic behavior
    if((0 <= mLineWrap) && (left > mLeft + mLineWrap))
    {
      top += 12 + 2; // replace with top member viriable plus linespace
      left = mLeft;
    }

    mVertexes[i] = Rect(left, top + mpFont->getYBearing(mText[i], mCharSize) + 
    mpFont->getYDescent(mText[i], mCharSize), dim.y - 1,dim.x - 1, lg::Black).getVertex()[0];
  
    std::cout << mpFont->getOffset(mText[i], mCharSize);
    std::cout << temp.getSize();
    VertexUtility::updateTextureCoordinates(mVertexes[i], Vector2<float>(dim.x, dim.y), 
                                            mpFont->getOffset(mText[i], mCharSize),
                                            temp.getSize());

    mVertexesData[i].QuadVertex = Rect(left, top + mpFont->getYBearing(mText[i], mCharSize) + 
    mpFont->getYDescent(mText[i], mCharSize), dim.y - 1,dim.x - 1, lg::Black).getVertex()[0];
    mVertexesData[i].Dimensions = Vector2<float>(dim.x, dim.y);

    left += dim.x + 1;
  }
}

//! @brief Gets Vertex Data
//!
//! @return Vertex Data
std::vector<Vertex> Text::getVertex()
{
  return mVertexes;
}

//! @brief Gets Vertex Data
//!
//! @return Vertex Data
std::vector<VertexData> Text::getVertexData()
{
  return mVertexesData;
}


//! @brief Get Texture Resource for Drawable
//!
//! @return Texture Resource
TextureResource& Text::getResource()
{
  return mpFont->getResource(mCharSize);
}

Text::~Text()
{
  std::cout << mRenderId << " Being destructed now.\n";
}