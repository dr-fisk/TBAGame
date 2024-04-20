#include <limits>

#include "drawable/text.hpp"
#include "renderer/renderer2D.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
  mpTexture = mpFont->getResource(mCharSize);

  gridfitText(crPos);
  mGeometryNeedUpdate = false;
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
  mGeometryNeedUpdate = true;
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
  mTextVertexes.clear();
  mTextVertexes.reserve(mText.size());
  size = mpTexture->getSize();
  TextVertexData tempTextVert;

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
    tempTextVert.Pos = pos;
    tempTextVert.Size = dim;
    updateTextureCoordinates(offset, dim, tempTextVert.Vertexes);
    mTextVertexes.push_back(tempTextVert);
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
  if(mRender)
  {
    if(mGeometryNeedUpdate)
    {
      gridfitText(mBox.getTopLeft());
    }
    
    for(auto& vertex : mTextVertexes)
    {
      Renderer2D::registerQuad(vertex.Pos, vertex.Size, vertex.Vertexes, mpTexture, mGeometryNeedUpdate);
    }

    mGeometryNeedUpdate = false;
  }
}

//! @brief Check if Text has a resource
//!
//! @return true if Text has resource false otherwise
bool Text::hasResource()
{
  return nullptr != mpTexture;
}

//! @brief Moves Position by adding x and y values
//!
//! @param[in] crMoveVector Vector values to move Text
//!
//! @return None
void Text::movePos(const glm::vec2& crMoveVector)
{
  mBox.movePos(crMoveVector);
  mGeometryNeedUpdate = true;
}

//! @brief Sets Text Position
//!
//! @param[in] crPos New Text Position
//!
//! @return None
void Text::setPos(const glm::vec2& crPos)
{
  mBox.setTopLeft(crPos);
  mGeometryNeedUpdate = true;
}

//! @brief Grabs Text String
//!
//! @return Text
std::string Text::getText() const
{
  return mText;
}

//! @brief Gets Size of Text
//!
//! @return Size of Text
glm::vec2 Text::getSize() const
{
  return mBox.getSize();
}

//! @brief Returns Text Position
//!
//! @return Text Position 
glm::vec2 Text::getPos() const
{
  return mBox.getPos();
}

//! @brief Destructor
//!
//! @return None
Text::~Text()
{
}

//! @brief  Updates texture coordinates for Text
//!
//! @param[in]  crOffset         Offset of Texture within Texture resource 
//! @param[in]  crTextureSize    Total Texture Size
//! @param[out] rTextCoords      The Text Coords Array to update
//!
//! @return None 
void Text::updateTextureCoordinates(const glm::vec2& crOffset, const glm::vec2& crTextureSize,
                                    std::array<Vertex, sNumQuadVerts>& rVertexes)
{
  const float xMax = static_cast<float>(crTextureSize.x + crOffset.x) / static_cast<float>(mpTexture->getSize().x);
  const float yMax = static_cast<float>(crTextureSize.y + crOffset.y) / static_cast<float>(mpTexture->getSize().y);
  const float xMin = static_cast<float>(crOffset.x) / static_cast<float>(mpTexture->getSize().x);
  const float yMin = static_cast<float>(crOffset.y) / static_cast<float>(mpTexture->getSize().y);

  rVertexes[3].TextCoord = glm::vec2(xMin, yMin);
  rVertexes[2].TextCoord = glm::vec2(xMax, yMin);
  rVertexes[1].TextCoord = glm::vec2(xMax, yMax);
  rVertexes[0].TextCoord = glm::vec2(xMin, yMax);
}

//! @brief 
//! @param crCamera 
//! @return 
Box<glm::vec2> Text::getGlobalBounds(const OrthCamera& crCamera) const
{
  const glm::vec4 TOP_LEFT = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  const glm::vec4 BOTTOM_RIGHT = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(mBox.getTopLeft(), 0.0f)) * glm::scale(glm::mat4(1.0f),
                                      {mBox.getSize().x, mBox.getSize().y, 1.0f});
  glm::vec2 topLeft = crCamera.getViewProjectionMatrix() * transform * TOP_LEFT;
  glm::vec2 size = crCamera.getViewProjectionMatrix() * transform * BOTTOM_RIGHT;
  size = abs(size - topLeft);
  return Box<glm::vec2>::createBoxTopLeft(topLeft, size);
}

void Text::setFont(std::shared_ptr<Font>& prFont)
{
  mpFont = prFont;
}

void Text::setFontSize(const uint8_t cCharSize, std::shared_ptr<RenderEngine>& prRenderEngine)
{
  if(mpFont)
  {    
    mCharSize = cCharSize;

    if(!mpFont->hasGlyphsLoaded(mCharSize))
    {
      mpFont->loadGlyphs(mCharSize, prRenderEngine);
    }

    mCapHeight = mpFont->getCapitalHeight();
    mAdvancedWidth = (static_cast<float>(mpFont->getAdvancedWidth()) / static_cast<float>(mpFont->getCapitalHeight()))
                    * (mCharSize - 1);
    mpTexture = mpFont->getResource(mCharSize);

    mGeometryNeedUpdate = true;
  }
}

void Text::setLineWrap(const bool cEnable)
{
  mLineWrap = cEnable;
  mGeometryNeedUpdate = true;
}