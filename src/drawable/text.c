#include "drawable/text.h"
#include "drawable/rectangle.h"
#include "utility/vertexUtility.h"

//! @brief Text Constructor
//!
//! @param[in]  prFont         Font Object to be used when rendering Text
//! @param[in]  crText         String to be rendered
//! @param[out] prRenderEngine Resource Manager to create Texture Resource
//! @param[out] prBatch        BatchBuffer to register drawable
//! @param[in]  cCharSize      Font Size
//! @param[in]  cTop           Top position of Text
//! @param[in]  cLeft          Left Position of Text
//! @param[in]  cLineWrap      Number of pixels before line of texts wraps under
//! @param[in]  cLineHeight    Height of Line multiplier
//!
//! @return Text Object 
Text::Text(std::shared_ptr<Font>& prFont, const std::string& crText, std::shared_ptr<RenderEngine>& prRenderEngine,
           std::shared_ptr<BatchBuffer>& prBatch, const uint8_t cCharSize, const float cTop, const float cLeft,
           const int32_t cLineWrap, const float cLineHeight)
{
  mpFont = prFont;
  mText = crText;
  mPos.y = cTop;
  mPos.x = cLeft;
  mLineWrap = cLineWrap;
  mCharSize = cCharSize;

  if(!mpFont->hasGlyphsLoaded(mCharSize))
  {
    mpFont->loadGlyphs(mCharSize, prRenderEngine);
  }

  mCapHeight = mpFont->getCapitalHeight();
  mAdvancedWidth = (static_cast<float>(mpFont->getAdvancedWidth()) / static_cast<float>(mpFont->getCapitalHeight())) 
                   * (mCharSize - 1);
  mLineSpace = std::ceil(cLineHeight * mCharSize);
  mTexture = mpFont->getResource(mCharSize);

  gridfitText();
  registerDrawable(prBatch, mTexture->getTextureId());
}

//! @brief Updates Text to be rendered
//!
//! @param[in] crText Text to be rendered
//!
//! @return None
void Text::updateText(const std::string& crText)
{
  mText.clear();
  mText = crText;
  mNeedUpdate = true;
}

//! @brief Creates layout of Text
//!
//! @return None
void Text::gridfitText()
{
  Vector2<uint32_t> dim(0,0);
  Vector2<uint32_t> offset(0,0);
  Vector2<uint32_t> size(0,0);
  float top = mPos.y;
  float left = mPos.x;
  Vector2<float> pos(0.0f, 0.0f);
  Vector2<float> textCoord(0.0f, 0.0f);
  lg::Color color = lg::Black;
  Vertex tempVert;
  mVertexes.clear();
  mVertexes.reserve(mText.size());

  for(size_t i = 0; i < mText.size(); i ++)
  {
    // Update for more dynamic behavior
    if((0 <= mLineWrap) && (left > mPos.x + mLineWrap))
    {
      top += mLineSpace; // replace with top member variable plus linespace
      left = mPos.x;
    }

    switch(static_cast<uint8_t>(mText[i]))
    {
      case U' ':
        left += mAdvancedWidth;
        continue;
      case U'\n':
        top += mLineSpace; // replace with top member variable plus linespace
        left = mPos.x;
        continue;
      case U'\t':
        left += (mAdvancedWidth * 4);
        continue;
    }

    pos.x = left;
    pos.y = top;

    dim = mpFont->getCharacterDimensions(mCharSize, mText[i]);
    pos.y += mpFont->getYBearing(mText[i], mCharSize) + mpFont->getYDescent(mText[i], mCharSize);
    textCoord.x = dim.x;
    textCoord.y = dim.y;
    color = lg::Black;
    offset = mpFont->getOffset(mText[i], mCharSize);
    size = mTexture->getSize();
    VertexUtility::updateVertex(tempVert, pos, dim, color);
    VertexUtility::updateTextureCoordinates(tempVert, textCoord, offset, size);

    mVertexes.push_back(tempVert);

    left += dim.x;
  }

  mDimensions.x = left - mPos.x;
  mDimensions.y = (top + mCharSize) - mPos.y;
}

//! @brief Get Texture Resource for Drawable
//!
//! @return Texture Resource
std::shared_ptr<TextureResource> Text::getResource()
{
  return mpFont->getResource(mCharSize);
}

//! @brief Grab all vertexes from Text Object
//!        Performs all updates needed for rendering
//!
//! @param[out] rBatchVertexes Vertex list
//! @param[out] rVertexIdx     Current index in vertex list
//!
//! @return None
void Text::getVertex(std::vector<Vertex>& rBatchVertexes, uint32_t& rVertexIdx)
{
  if(mNeedUpdate)
  {
    gridfitText();
    mNeedUpdate = false;
  }

  for(auto& vertex : mVertexes)
  {
    if(mTexture->updateTextureIndex())
    {
      VertexUtility::setVertexTextureIndex(vertex, static_cast<float>(mTexture->getCacheId()));
    }

    rBatchVertexes[rVertexIdx] = vertex;
    rVertexIdx ++;
  }
}

//! @brief Check if Text Texture Resource is Bounded
//!
//! @return true if Texture is bounded false otherwise
bool Text::textureBounded()
{
  return mTexture->isBounded();
}

//! @brief Check if Text has a resource
//!
//! @return true if Text has resource false otherwise
bool Text::hasResource()
{
  return nullptr != mTexture;
}

//! @brief Moves Position by adding x and y values
//!
//! @param[in] cX X value to add
//! @param[in] cY Y value to add
//!
//! @return None
void Text::movePos(const float cX, const float cY)
{
  mPos.x += cX;
  mPos.y += cY;

  mNeedUpdate = true;
}

//! @brief Grabs Text String
//!
//! @return Text
std::string Text::getText()
{
  return mText;
}

//! @brief Sets Position
//!
//! @param[in] cLeft Left Position
//! @param[in] cTop  Top Position
//!
//! @return None
void Text::setPos(const float cLeft, const float cTop)
{
  mPos.x = cLeft;
  mPos.y = cTop;

  mNeedUpdate = true;
}

//! @brief Gets Size of Text
//!
//! @return Size of Text
Vector2<uint32_t> Text::getSize()
{
  return mDimensions;
}

//! @brief Returns Text Position
//!
//! @return Text Position 
Vector2<float> Text::getPos()
{
  return mPos;
}

//! @brief Destructor
//!
//! @return None
Text::~Text()
{
  if(0 != mRenderId && nullptr != mTexture)
  {
    mpBatch->unregisterDrawable(mRenderId, mTexture->getTextureId());
  }
}