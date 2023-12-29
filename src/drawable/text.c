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

  float top = mTop;
  float left = mLeft;
  std::shared_ptr<TextureResource> temp = getResource();
  float textureId = temp->getCacheId();

  for(size_t i = 0; i < mText.size(); i ++)
  {
    dim = mpFont->getCharacterDimensions(mCharSize, mText[i]);
    dim.x --;
    dim.y --;

    // Update for more dynamic behavior
    if((0 <= mLineWrap) && (left > mLeft + mLineWrap))
    {
      top += 12 + 2; // replace with top member viriable plus linespace
      left = mLeft;
    }

    VertexUtility::createVertex(mVertexes[i], Vector2<float>(left, top + mpFont->getYBearing(mText[i], mCharSize) + 
                                mpFont->getYDescent(mText[i], mCharSize)), dim, lg::Black, textureId); 
  
    VertexUtility::updateTextureCoordinates(mVertexes[i], Vector2<float>(dim.x, dim.y), 
                                            mpFont->getOffset(mText[i], mCharSize),
                                            temp->getSize());

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

//! @brief Destructor
//!
//! @return None
Text::~Text()
{
  std::cout << mRenderId << " Being destructed now.\n";
}