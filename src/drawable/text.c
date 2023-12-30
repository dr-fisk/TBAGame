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
           std::shared_ptr<BatchBuffer>& prBatch, const uint8_t cCharSize, const float cTop, const float cLeft,
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

  mCapHeight = mpFont->getCapitalHeight();
  mAdvancedWidth = (static_cast<float>(mpFont->getAdvancedWidth()) / static_cast<float>(mpFont->getCapitalHeight())) 
                   * (mCharSize - 1);

  //Replace with paramters
  mVertexes.resize(mText.size());

  gridfitText();
}

//! @brief Updates Text to be rendered
//!
//! @param[in] crText Text to be rendered
//!
//! @return None
void Text::updateText(const std::string& crText)
{
  mVertexes.clear();
  mText.clear();
  mText = crText;
  mVertexes.resize(mText.size());
  gridfitText();
}

//! @brief Creates layout of Text
//!
//! @return None
void Text::gridfitText()
{
  Vector2<uint32_t> dim(0,0);
  Vector2<uint32_t> offset(0,0);
  Vector2<uint32_t> size(0,0);
  float top = mTop;
  float left = mLeft;
  std::shared_ptr<TextureResource> temp = getResource();
  float textureId = 0.0f;
  Vector2<float> pos(0.0f, 0.0f);
  Vector2<float> textCoord(0.0f, 0.0f);
  lg::Color color = lg::Black;

  for(size_t i = 0; i < mText.size(); i ++)
  {
    // Update for more dynamic behavior
    if((0 <= mLineWrap) && (left > mLeft + mLineWrap))
    {
      top += 12 + 2; // replace with top member viriable plus linespace
      left = mLeft;
    }

    pos.x = left;
    pos.y = top;

    if(isspace(mText[i]))
    {
      dim = Vector2<uint32_t>(mAdvancedWidth, mCharSize - 1);
      color = lg::Transparent;
      textureId = -1.0f;
      textCoord.x = dim.x;
      textCoord.y = dim.y;
      size = dim;
    }
    else
    {
      dim = mpFont->getCharacterDimensions(mCharSize, mText[i]);
      pos.y += mpFont->getYBearing(mText[i], mCharSize) + mpFont->getYDescent(mText[i], mCharSize);
      textCoord.x = dim.x;
      textCoord.y = dim.y;
      color = lg::Black;
      textureId = static_cast<float>(temp->getCacheId());
      offset = mpFont->getOffset(mText[i], mCharSize);
      size = temp->getSize();
    }

    VertexUtility::createVertex(mVertexes[i], pos, dim, color, textureId);
    VertexUtility::updateTextureCoordinates(mVertexes[i], textCoord, offset, size);

    left += dim.x + 1;
  }
}

//! @brief Get Texture Resource for Drawable
//!
//! @return Texture Resource
std::shared_ptr<TextureResource> Text::getResource()
{
  return mpFont->getResource(mCharSize);
}

//! @brief Check if Drawable needs Vertexes updated
//!
//! @return true if update need false otherwise
bool Text::needUpdate()
{
  return mNeedUpdate | mpFont->getResource(mCharSize)->updateTextureIndex();
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
  std::shared_ptr<TextureResource> temp = mpFont->getResource(mCharSize);
  for(auto& vertex : mVertexes)
  {
    if(mNeedUpdate)
    {
      // do this
    }

    if(temp->updateTextureIndex())
    {
      VertexUtility::setVertexTextureIndex(vertex, static_cast<float>(temp->getCacheId()));
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
  return mpFont->getResource(mCharSize)->isBounded();
}

//! @brief Check if Text has a resource
//!
//! @return true if Text has resource false otherwise
bool Text::hasResource()
{
  return mpFont->getResource(mCharSize) != nullptr;
}

//! @brief Destructor
//!
//! @return None
Text::~Text()
{
  std::cout << mRenderId << " Being destructed now.\n";
}

void Text::movePos(float cX, float cY)
{
  mLeft += cX;
  mTop += cY;

  gridfitText();
}