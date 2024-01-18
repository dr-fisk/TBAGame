#include <limits>

#include "drawable/text.h"
#include "utility/vertexUtility.h"
#include "renderer/renderer2D.h"

//! @brief Text Constructor
//!
//! @param[in]  prFont         Font Object to be used when rendering Text
//! @param[in]  crText         String to be rendered
//! @param[out] prRenderEngine Resource Manager to create Texture Resource
//! @param[in]  cCharSize      Font Size
//! @param[in]  crPos          Position of Text
//! @param[in]  cLineWrap      Number of pixels before line of texts wraps under
//! @param[in]  cLineHeight    Height of Line multiplier
//!
//! @return Text Object 
Text::Text(std::shared_ptr<Font>& prFont, const std::string& crText, std::shared_ptr<RenderEngine>& prRenderEngine,
           const uint8_t cCharSize, const glm::vec2& crPos,
           const int32_t cLineWrap, const float cLineHeight)
{
  mpFont = prFont;
  mText = crText;
  mLayer = std::numeric_limits<uint32_t>::max();

  // mBox.setPos({cLeft, cTop});
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

  gridfitText(crPos);
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
void Text::gridfitText(const glm::vec2& crTopLeft)
{
  glm::uvec2 dim(0,0);
  glm::uvec2 offset(0,0);
  glm::uvec2 size(0,0);
  float top = crTopLeft.y;
  float left = crTopLeft.x;
  glm::vec2 pos(0.0f, 0.0f);
  glm::vec2 textCoord(0.0f, 0.0f);
  lg::Color color = lg::Black;
  Vertex tempVert;
  mVertexes.clear();
  mVertexes.reserve(mText.size());

  for(size_t i = 0; i < mText.size(); i ++)
  {
    // Update for more dynamic behavior
    if((0 <= mLineWrap) && (left > crTopLeft.x + mLineWrap))
    {
      top += mLineSpace; // replace with top member variable plus linespace
      left = crTopLeft.x;
    }

    switch(static_cast<uint8_t>(mText[i]))
    {
      case U' ':
        left += mAdvancedWidth;
        continue;
      case U'\n':
        top += mLineSpace; // replace with top member variable plus linespace
        left = crTopLeft.x;
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
    VertexUtility::setVertexTextureIndex(tempVert, static_cast<float>(mTexture->getCacheId()));
    VertexUtility::updateTextureCoordinates(tempVert, textCoord, offset, size);

    mVertexes.push_back(tempVert);

    left += dim.x;
  }

  mBox.setBoxTopLeft(crTopLeft, {left - crTopLeft.x, (top + mCharSize) - crTopLeft.y});
}

//! @brief Get Texture Resource for Drawable
//!
//! @return Texture Resource
std::shared_ptr<TextureResource> Text::getResource()
{
  return mpFont->getResource(mCharSize);
}

//! @brief Draws the Text
//!
//! @return None
void Text::draw()
{
  if(mNeedUpdate)
  {
    gridfitText(mBox.getTopLeft());
    mNeedUpdate = false;
  }

  if(mRender)
  {
    for(auto& vertex : mVertexes)
    {
      Renderer2D::registerQuad(vertex, mTexture);
    }
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
//! @param[in] crMoveVector Vector values to move Text
//!
//! @return None
void Text::movePos(const glm::vec2& crMoveVector)
{
  mBox.movePos(crMoveVector);
  mNeedUpdate = true;
}

//! @brief Sets Text Position
//!
//! @param[in] crPos New Text Position
//!
//! @return None
void Text::setPos(const glm::vec2& crPos)
{
  mBox.setTopLeft(crPos);
  mNeedUpdate = true;
}

//! @brief Grabs Text String
//!
//! @return Text
std::string Text::getText()
{
  return mText;
}

//! @brief Gets Size of Text
//!
//! @return Size of Text
glm::vec2 Text::getSize()
{
  return mBox.getSize();
}

//! @brief Returns Text Position
//!
//! @return Text Position 
glm::vec2 Text::getPos()
{
  return mBox.getPos();
}

//! @brief Destructor
//!
//! @return None
Text::~Text()
{
}