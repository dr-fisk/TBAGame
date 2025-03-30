#include <limits>
#include <algorithm>

#include "drawable/text.hpp"
#include "renderer/renderer2D.hpp"
#include "glm/gtc/matrix_transform.hpp"


Text::Text() : mpFont(nullptr), mpTexture(nullptr)
{
  mBox.setTopLeft({0, 0});
}

//! @brief Text Constructor
//!
//! @param[in]  crFont         Font Object to be used when rendering Text
//! @param[in]  crText         String to be rendered
//! @param[in]  cCharSize      Font Size
//!
//! @return Text Object 
Text::Text(const Font& crFont, const std::string& crText, const uint8_t cCharSize)
{
  mpFont = &crFont;
  mText = crText;
  mCharSize = cCharSize;

  if(!mpFont->hasGlyphsLoaded(mCharSize))
  {
    mpFont->loadGlyphs(mCharSize);
  }

  mBox.setTopLeft({0, 0});
  mCapHeight = mpFont->getCapitalHeight();
  mAdvancedWidth = (static_cast<float>(mpFont->getAdvancedWidth()) / static_cast<float>(mpFont->getCapitalHeight())) 
                   * (mCharSize - 1);
  mLineSpace = std::ceil(1.2f * mCharSize);
  mpTexture = &mpFont->getTexture(mCharSize);
  gridfitText(mBox.getTopLeft());
  mGeometryNeedUpdate = false;
}

//! @brief Updates Text to be rendered
//!
//! @param[in] crString Text to be rendered
//!
//! @return None
Text& Text::setString(const std::string& crString)
{
  mText.clear();
  mText = crString;
  gridfitText(mBox.getTopLeft());
  mGeometryNeedUpdate = false;
  return *this;
}

//! @brief Creates layout of Text
//!
//! @return None
void Text::gridfitText(const glm::vec2& crTopLeft)
{
  if(!mpFont)
  {
    return;
  }

  glm::uvec2 dim(0,0);
  glm::uvec2 offset(0,0);
  float top = crTopLeft.y;
  float left = crTopLeft.x;
  glm::vec2 pos(0.0f, 0.0f);
  glm::vec2 textCoord(0.0f, 0.0f);
  Vertex tempVert;
  mTextVertexes.clear();
  mTextVertexes.reserve(mText.size());
  TextVertexData tempTextVert;
  const float WHITE_SPACE_WIDTH = mpFont->getCharacterDimensions(mCharSize, ' ').x;
  int16_t prevRsb = 0;

  for(size_t i = 0; i < mText.size(); i ++)
  {
    // Update for more dynamic behavior
    if((0 <= mLineWrap) && (left > crTopLeft.x + mLineWrap))
    {
      top += mLineSpace; // replace with top member variable plus linespace
      left = crTopLeft.x;
    }

    if((mText[i] == U' ') || (mText[i] == U'\n') || (mText[i] == U'\t'))
    {
      switch(static_cast<uint8_t>(mText[i]))
      {
        case U' ':
          left += WHITE_SPACE_WIDTH;
          break;
        case U'\n':
          top += mLineSpace;
          left = crTopLeft.x;
          break;
        case U'\t':
          left += (WHITE_SPACE_WIDTH * 4);
          break;
      }

      continue;
    }

    pos.x = left;
    pos.y = top;

    dim = mpFont->getCharacterDimensions(mCharSize, mText[i]);
    pos.y += mpFont->getYHint(mText[i], mCharSize);
    pos.x += mpFont->getLeftSideBearing(mText[i], mCharSize);
    textCoord.x = dim.x;
    textCoord.y = dim.y;
    offset = mpFont->getOffset(mText[i], mCharSize);
    tempTextVert.Pos = pos;
    tempTextVert.Size = dim;
    updateTextureCoordinates(offset, dim, tempTextVert.Vertexes);
    updateQuadColor(tempTextVert.Vertexes);

    mTextVertexes.push_back(tempTextVert);
    left += mpFont->getAdvancedWidth(mText[i], mCharSize);
  }

  mBox.setBoxTopLeft(crTopLeft, {left - crTopLeft.x, (top + mCharSize) - crTopLeft.y});
}

//! @brief Get Texture for Drawable
//!
//! @return Texture
const Texture2D& Text::getTexture() const
{
  return *mpTexture;
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
Text& Text::setPos(const glm::vec2& crPos)
{
  mBox.setTopLeft(crPos);
  mGeometryNeedUpdate = true;
  return *this;
}

//! @brief Grabs Text String
//!
//! @return Text
std::string& Text::getString()
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

//! @brief  Attaches font to text
//!
//! @param[in] crFont 
//!
//! @return None
Text& Text::setFont(const Font& crFont)
{
  mpFont = &crFont;
  return *this;
}

Text& Text::setFontSize(const uint8_t cCharSize)
{
  if(mpFont)
  {    
    mCharSize = cCharSize;

    if(!mpFont->hasGlyphsLoaded(mCharSize))
    {
      mpFont->loadGlyphs(mCharSize);
    }

    mCapHeight = mpFont->getCapitalHeight();
    mAdvancedWidth = (static_cast<float>(mpFont->getAdvancedWidth()) / static_cast<float>(mpFont->getCapitalHeight()))
                    * (mCharSize - 1);
    mpTexture = &mpFont->getTexture(mCharSize);

    mGeometryNeedUpdate = true;
  }

  return *this;
}

//! @brief Enables/disables linewrap functionality
//!
//! @param[in] cEnable Enable/Disable boolean
//!
//! @return Text reference to chain setters
Text& Text::setLineWrap(const bool cEnable)
{
  mLineWrap = cEnable;
  mGeometryNeedUpdate = true;
  return *this;
}

//! @brief Inserts string to text object
//!
//! @param[in] crString String to append
//! @param[in] cIndex   Index to append string to
//!
//! @return None
void Text::insertString(const std::string& crString, const size_t cIndex)
{
  mText.insert(cIndex, crString);
  mGeometryNeedUpdate = true;
}

//! @brief Appends string to end of text object
//!
//! @param[in] crString String to append
//!
//! @return None 
void Text::appendString(const std::string& crString)
{
  mText += crString;
  mGeometryNeedUpdate = true;
}

//! @brief Gets the length of string member variable
//!
//! @return Length of String member variable 
size_t Text::getLength() const
{
  return mText.size();
}

//! @brief Sets the fill color for text
//!
//! @param[in] crColor Fill color
//! 
//! @return Text reference to chain setters 
Text& Text::setColor(const lg::Color &crColor)
{
  mColor = crColor;
  mGeometryNeedUpdate = true;
  return *this;
}

//! @brief Updates vertexes to fill color
//!
//! @param[out] rVertexes Vertexes to set fill color on
//!
//! @return None
void Text::updateQuadColor(std::array<Vertex, sNumQuadVerts>& rVertexes)
{
  rVertexes[3].OverrideSampleColor = 1.0f;
  rVertexes[2].OverrideSampleColor = 1.0f;
  rVertexes[1].OverrideSampleColor = 1.0f;
  rVertexes[0].OverrideSampleColor = 1.0f;
  rVertexes[3].Rgba = mColor;
  rVertexes[2].Rgba = mColor;
  rVertexes[1].Rgba = mColor;
  rVertexes[0].Rgba = mColor;
}

//! @brief Gets font character size
//!
//! @return Font character size 
uint8_t Text::getCharSize() const
{
  return mCharSize;
}

std::vector<Box<glm::vec2>> Text::getBoundingBoxes() const
{
  std::vector<Box<glm::vec2>> temp;
  temp.reserve(mText.size());
  
  for(const auto& data : mTextVertexes)
  {
    temp.push_back({data.Pos, data.Size});
  }

  return temp;
}

const std::string& Text::getString() const
{
  return mText;
}

glm::vec2 Text::getCharPos(const int cCharIndex) const
{
  return mTextVertexes.at(cCharIndex).Pos;
}

glm::vec2 Text::getCharSize(const int cCharIndex) const
{
  return mTextVertexes.at(cCharIndex).Size;
}