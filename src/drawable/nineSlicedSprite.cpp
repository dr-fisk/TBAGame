#include "drawable/nineSlicedSprite.hpp"
#include "renderer/renderer2D.hpp"

SlicedSprite::SlicedSprite()
{
  mSlicedQuads.try_emplace(NineSliceTypes::TOP_LEFT);
  mSlicedQuads.try_emplace(NineSliceTypes::TOP_CENTER);
  mSlicedQuads.try_emplace(NineSliceTypes::TOP_RIGHT);
  mSlicedQuads.try_emplace(NineSliceTypes::MID_LEFT);
  mSlicedQuads.try_emplace(NineSliceTypes::MID_CENTER);
  mSlicedQuads.try_emplace(NineSliceTypes::MID_RIGHT);
  mSlicedQuads.try_emplace(NineSliceTypes::BOTTOM_LEFT);
  mSlicedQuads.try_emplace(NineSliceTypes::BOTTOM_CENTER);
  mSlicedQuads.try_emplace(NineSliceTypes::BOTTOM_RIGHT);
  mpTexture = nullptr;
}

SlicedSprite& SlicedSprite::setColor(const lg::Color& crColor)
{
  SlicedQuadData& data = mSlicedQuads.at(NineSliceTypes::MID_CENTER);
  data.Vertexes[0].Rgba = crColor;
  data.Vertexes[1].Rgba = crColor;
  data.Vertexes[2].Rgba = crColor;
  data.Vertexes[3].Rgba = crColor;
  data.UseTexture = false;
  return *this;
}

void SlicedSprite::movePos(const glm::vec2& crMoveVector)
{

}

SlicedSprite& SlicedSprite::setPos(const glm::vec2& crPos)
{
  mTransform.setPos(crPos);
  mGeometryNeedUpdate = true;
  return *this;
}

SlicedSprite& SlicedSprite::resize(const glm::vec2& crSize)
{
  mTransform.setScale(crSize);
  mGeometryNeedUpdate = true;
  return *this;
}

SlicedSprite& SlicedSprite::setTransform(const Transform& crTransform)
{
  mTransform = crTransform;
  mGeometryNeedUpdate = true;
  return *this;
}

SlicedSprite& SlicedSprite::setTexture(const Texture2D& crTexture, const bool cInvert)
{
  mpTexture = &crTexture;
  mBox2D.left = 0;
  mBox2D.top = 0;
  mBox2D.width = crTexture.getSize().x;
  mBox2D.height = crTexture.getSize().y;
  updateTextureCoordinates({0.0f, 0.0f}, crTexture.getSize());
  return *this;
}

SlicedSprite& SlicedSprite::setBox(const Box<glm::vec2>& crBox)
{
  return *this;
}

void SlicedSprite::updateTextureCoordinates(const glm::vec2& crOffset, const glm::vec2& crTextureSize)
{
  // 1   ->    2
  //           |
  //           v
  // 4   <-    3

  glm::vec2 offset = crOffset;

  for(auto& quad : mSlicedQuads)
  {

    setOffset(quad.first, crOffset, offset);
    quad.second.UseTexture = true;
    quad.second.Vertexes[0].TextCoord = offset / static_cast<glm::vec2>(mpTexture->getSize());

    switch(quad.first)
    {
      case NineSliceTypes::TOP_LEFT:
        quad.second.Vertexes[1].TextCoord = glm::vec2{offset.x + mLeft, offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[2].TextCoord = glm::vec2{offset.x + mLeft, offset.y + mTop} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[3].TextCoord = glm::vec2{offset.x, offset.y + mTop} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::TOP_CENTER:
        quad.second.Vertexes[1].TextCoord = glm::vec2{offset.x + mpTexture->getSize().x - (mRight + 1), offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[2].TextCoord = glm::vec2{offset.x + mpTexture->getSize().x - (mRight + 1), offset.y + mTop} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[3].TextCoord = glm::vec2{offset.x, offset.y + mTop} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::TOP_RIGHT:
        quad.second.Vertexes[1].TextCoord = glm::vec2{offset.x + mRight, offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[2].TextCoord = glm::vec2{offset.x + mRight, offset.y + mTop} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[3].TextCoord = glm::vec2{offset.x, offset.y + mTop} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::MID_LEFT:
        quad.second.Vertexes[1].TextCoord = glm::vec2{offset.x + mLeft, offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[2].TextCoord = glm::vec2{offset.x + mLeft, mpTexture->getSize().y - mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[3].TextCoord = glm::vec2{offset.x, mpTexture->getSize().y - mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::MID_CENTER:
        quad.second.Vertexes[1].TextCoord = glm::vec2{mpTexture->getSize().x - (mRight + 1), offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[2].TextCoord = glm::vec2{mpTexture->getSize().x - (mRight + 1), mpTexture->getSize().y - mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[3].TextCoord = glm::vec2{offset.x, mpTexture->getSize().y - mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::MID_RIGHT:
        quad.second.Vertexes[1].TextCoord = glm::vec2{offset.x + mRight, offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[2].TextCoord = glm::vec2{offset.x + mRight, mpTexture->getSize().y - mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[3].TextCoord = glm::vec2{offset.x, mpTexture->getSize().y - mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::BOTTOM_LEFT:
        quad.second.Vertexes[1].TextCoord = glm::vec2{offset.x + mLeft, offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[2].TextCoord = glm::vec2{offset.x + mLeft, offset.y + mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[3].TextCoord = glm::vec2{offset.x, offset.y + mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::BOTTOM_CENTER:
        quad.second.Vertexes[1].TextCoord = glm::vec2{offset.x + mpTexture->getSize().x - (mRight + 1), offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[2].TextCoord = glm::vec2{offset.x + mpTexture->getSize().x - (mRight + 1), offset.y + mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[3].TextCoord = glm::vec2{offset.x, offset.y + mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::BOTTOM_RIGHT:
        quad.second.Vertexes[1].TextCoord = glm::vec2{offset.x + mRight, offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[2].TextCoord = glm::vec2{offset.x + mRight, offset.y + mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second.Vertexes[3].TextCoord = glm::vec2{offset.x, offset.y + mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
    }
  }
}

void SlicedSprite::setOffset(const NineSliceTypes cType, const glm::vec2& crOffset, glm::vec2& rResult)
{
  switch(cType)
  {
    case NineSliceTypes::TOP_LEFT:
      rResult = crOffset;
      break;
    case NineSliceTypes::TOP_CENTER:
      rResult = {crOffset.x + mLeft + 1, crOffset.y};
      break;
    case NineSliceTypes::TOP_RIGHT:
      rResult = {crOffset.x + mpTexture->getSize().x - mRight, crOffset.y};
      break;
    case NineSliceTypes::MID_LEFT:
      rResult = {crOffset.x, crOffset.y + mTop};
      break;
    case NineSliceTypes::MID_CENTER:
      rResult = {crOffset.x + mLeft + 1, crOffset.y + mTop + 1};
      break;
    case NineSliceTypes::MID_RIGHT:
      rResult = {crOffset.x + mpTexture->getSize().x - mRight, crOffset.y + mTop};
      break;
    case NineSliceTypes::BOTTOM_LEFT:
      rResult = {crOffset.x, mpTexture->getSize().y - mBottom};
      break;
    case NineSliceTypes::BOTTOM_CENTER:
      rResult = {crOffset.x + mLeft + 1, mpTexture->getSize().y - mBottom};
      break;
    case NineSliceTypes::BOTTOM_RIGHT:
      rResult = {crOffset.x + mpTexture->getSize().x - mRight, mpTexture->getSize().y - mBottom};
      break;
  }
}

void SlicedSprite::draw()
{
  if(mGeometryNeedUpdate)
  {
    updateGeometry();
    mGeometryNeedUpdate = false;
  }

  // If no borders set, then don't bother drawing the other 8 quads and only draw center
  if(0 == mTop && 0 == mLeft && 0 == mRight && 0 == mBottom)
  {
    SlicedQuadData& data = mSlicedQuads.at(NineSliceTypes::MID_CENTER);
    if(data.UseTexture)
    {
      Renderer2D::registerQuad(data.QuadTransform, data.Vertexes, mpTexture, data.QuadTransform.getScale() / 2.0f);
    }
    else
    {
      Renderer2D::registerQuad(data.QuadTransform, data.Vertexes, data.QuadTransform.getScale() / 2.0f);
    }
  }
  else
  {
    for(auto& quad : mSlicedQuads)
    {
      if(quad.second.UseTexture)
      {
        Renderer2D::registerQuad(quad.second.QuadTransform, quad.second.Vertexes, mpTexture, quad.second.QuadTransform.getScale() / 2.0f);
      }
      else
      {
        Renderer2D::registerQuad(quad.second.QuadTransform, quad.second.Vertexes, quad.second.QuadTransform.getScale() / 2.0f);
      }
    }
  }
}

void SlicedSprite::updateGeometry()
{
  const float X_SCALE =    mTransform.getScale().x - (mLeft + mRight);
  const float Y_SCALE =    mTransform.getScale().y - (mTop + mBottom);
  const float RIGHT_POS =  mTransform.getPos().x + ((X_SCALE + mRight) / 2.0f);
  const float LEFT_POS =   mTransform.getPos().x - ((X_SCALE + mLeft) / 2.0f);
  const float TOP_POS =    mTransform.getPos().y - ((Y_SCALE + mTop) / 2.0f);
  const float BOTTOM_POS = mTransform.getPos().y + ((Y_SCALE + mBottom) / 2.0f);

  for(auto& quad : mSlicedQuads)
  {
    switch(quad.first)
    {
      // Doesn't Scale
      case NineSliceTypes::TOP_LEFT:
        quad.second.QuadTransform.setScale({mLeft, mTop});
        quad.second.QuadTransform.setPos({LEFT_POS, TOP_POS});
        quad.second.QuadTransform.setRotation(mTransform.getRotation());
        break;
      // Only scales horiztonally
      case NineSliceTypes::TOP_CENTER:
        quad.second.QuadTransform.setScale({X_SCALE, mTop});
        quad.second.QuadTransform.setPos({mTransform.getPos().x, TOP_POS});
        quad.second.QuadTransform.setRotation(mTransform.getRotation());
        break;
      // Doesn't Scale
      case NineSliceTypes::TOP_RIGHT:
        quad.second.QuadTransform.setScale({mRight, mTop});
        quad.second.QuadTransform.setPos({RIGHT_POS, TOP_POS});
        quad.second.QuadTransform.setRotation(mTransform.getRotation());
        break;
      // Only scales vertically
      case NineSliceTypes::MID_LEFT:
        quad.second.QuadTransform.setScale({mLeft, Y_SCALE});
        quad.second.QuadTransform.setPos({LEFT_POS, mTransform.getPos().y});
        quad.second.QuadTransform.setRotation(mTransform.getRotation());
        break;
      // Scales both vertically and horizontally
      case NineSliceTypes::MID_CENTER:
        quad.second.QuadTransform.setScale({X_SCALE, Y_SCALE});
        quad.second.QuadTransform.setPos(mTransform.getPos());
        quad.second.QuadTransform.setRotation(mTransform.getRotation());
        break;
      // Only scales vertically
      case NineSliceTypes::MID_RIGHT:
        quad.second.QuadTransform.setScale({mRight, Y_SCALE});
        quad.second.QuadTransform.setPos({RIGHT_POS, mTransform.getPos().y});
        quad.second.QuadTransform.setRotation(mTransform.getRotation());
        break;
      // Doesn't Scale
      case NineSliceTypes::BOTTOM_LEFT:
        quad.second.QuadTransform.setScale({mLeft, mBottom});
        quad.second.QuadTransform.setPos({LEFT_POS, BOTTOM_POS});
        quad.second.QuadTransform.setRotation(mTransform.getRotation());
        break;
      // Only scales horiztonally
      case NineSliceTypes::BOTTOM_CENTER:
        quad.second.QuadTransform.setScale({X_SCALE, mBottom});
        quad.second.QuadTransform.setPos({mTransform.getPos().x, BOTTOM_POS});
        quad.second.QuadTransform.setRotation(mTransform.getRotation());
        break;
      // Doesn't Scale
      case NineSliceTypes::BOTTOM_RIGHT:
        quad.second.QuadTransform.setScale({mRight, mBottom});
        quad.second.QuadTransform.setPos({RIGHT_POS, BOTTOM_POS});
        quad.second.QuadTransform.setRotation(mTransform.getRotation());
        break;
    }
  }
}

glm::vec2 SlicedSprite::getSize() const
{
  return mTransform.getScale();
}

glm::vec2 SlicedSprite::getPos() const
{
  return mTransform.getPos();
}

void SlicedSprite::setSpecificBorder(const SliceBorder cBorder, const float cSize)
{
  switch(cBorder)
  {
    case SliceBorder::TOP:
      mTop = cSize;
      break;
    case SliceBorder::LEFT:
      mLeft = cSize;
      break;
    case SliceBorder::BOTTOM:
      mBottom = cSize;
      break;
    case SliceBorder::RIGHT:
      mRight = cSize;
      break;
    default:
      return;
  }

  mGeometryNeedUpdate = true;

  // Probably want a delayed update
  if(mpTexture)
  {
    updateTextureCoordinates({0.0f, 0.0f}, mpTexture->getSize());
  }
}

void SlicedSprite::setAllBorders(const float cLeft, const float cTop, const float cRight, const float cBottom)
{
  mTop = cTop;
  mLeft = cLeft;
  mRight = cRight;
  mBottom = cBottom;
  mGeometryNeedUpdate = true;

  // Probably want a delayed update
  if(mpTexture)
  {
    updateTextureCoordinates({0.0f, 0.0f}, mpTexture->getSize());
  }
}

void SlicedSprite::fillBorderColor(const lg::Color& crColor)
{
  for(auto& quad : mSlicedQuads)
  {
    switch(quad.first)
    {
      // All quads surrounding Mid center are borders
      case NineSliceTypes::TOP_LEFT:
      case NineSliceTypes::TOP_CENTER:
      case NineSliceTypes::TOP_RIGHT:
      case NineSliceTypes::MID_LEFT:
      case NineSliceTypes::MID_RIGHT:
      case NineSliceTypes::BOTTOM_LEFT:
      case NineSliceTypes::BOTTOM_CENTER:
      case NineSliceTypes::BOTTOM_RIGHT:
        quad.second.UseTexture = false;
        quad.second.Vertexes[0].Rgba = crColor;
        quad.second.Vertexes[1].Rgba = crColor;
        quad.second.Vertexes[2].Rgba = crColor;
        quad.second.Vertexes[3].Rgba = crColor;
        break;
      case NineSliceTypes::MID_CENTER:
        break;
    }
  }
}

void SlicedSprite::removeBorderColor()
{
  for(auto& quad : mSlicedQuads)
  {
    switch(quad.first)
    {
      // All quads surrounding Mid center are borders
      case NineSliceTypes::TOP_LEFT:
      case NineSliceTypes::TOP_CENTER:
      case NineSliceTypes::TOP_RIGHT:
      case NineSliceTypes::MID_LEFT:
      case NineSliceTypes::MID_RIGHT:
      case NineSliceTypes::BOTTOM_LEFT:
      case NineSliceTypes::BOTTOM_CENTER:
      case NineSliceTypes::BOTTOM_RIGHT:
        quad.second.UseTexture = true;
        quad.second.Vertexes[0].Rgba = lg::Transparent;
        quad.second.Vertexes[1].Rgba = lg::Transparent;
        quad.second.Vertexes[2].Rgba = lg::Transparent;
        quad.second.Vertexes[3].Rgba = lg::Transparent;
        break;
      case NineSliceTypes::MID_CENTER:
        break;
    }
  }
}