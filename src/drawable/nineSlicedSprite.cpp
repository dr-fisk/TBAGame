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

void SlicedSprite::draw(const Transform& crTransform)
{
  Transform actualTransform;
  const float X_SCALE =    crTransform.getScale().x - (mLeft + mRight);
  const float Y_SCALE =    crTransform.getScale().y - (mTop + mBottom);
  const float RIGHT_POS =  crTransform.getPos().x + ((X_SCALE + mRight) / 2.0f);
  const float LEFT_POS =   crTransform.getPos().x - ((X_SCALE + mLeft) / 2.0f);
  const float TOP_POS =    crTransform.getPos().y - ((Y_SCALE + mTop) / 2.0f);
  const float BOTTOM_POS = crTransform.getPos().y + ((Y_SCALE + mBottom) / 2.0f);

  for(auto& quad : mSlicedQuads)
  {
    switch(quad.first)
    {
      // Doesn't Scale
      case NineSliceTypes::TOP_LEFT:
        actualTransform.setScale({mLeft, mTop});
        actualTransform.setPos({LEFT_POS, TOP_POS});
        actualTransform.setRotation(crTransform.getRotation());
        break;
      // Only scales horiztonally
      case NineSliceTypes::TOP_CENTER:
        actualTransform.setScale({X_SCALE, mTop});
        actualTransform.setPos({crTransform.getPos().x, TOP_POS});
        actualTransform.setRotation(crTransform.getRotation());
        break;
      // Doesn't Scale
      case NineSliceTypes::TOP_RIGHT:
        actualTransform.setScale({mRight, mTop});
        actualTransform.setPos({RIGHT_POS, TOP_POS});
        actualTransform.setRotation(crTransform.getRotation());
        break;
      // Only scales vertically
      case NineSliceTypes::MID_LEFT:
        actualTransform.setScale({mLeft, Y_SCALE});
        actualTransform.setPos({LEFT_POS, crTransform.getPos().y});
        actualTransform.setRotation(crTransform.getRotation());
        break;
      // Scales both vertically and horizontally
      case NineSliceTypes::MID_CENTER:
        actualTransform.setScale({X_SCALE, Y_SCALE});
        actualTransform.setPos(crTransform.getPos());
        actualTransform.setRotation(crTransform.getRotation());
        break;
      // Only scales vertically
      case NineSliceTypes::MID_RIGHT:
        actualTransform.setScale({mRight, Y_SCALE});
        actualTransform.setPos({RIGHT_POS, crTransform.getPos().y});
        actualTransform.setRotation(crTransform.getRotation());
        break;
      // Doesn't Scale
      case NineSliceTypes::BOTTOM_LEFT:
        actualTransform.setScale({mLeft, mBottom});
        actualTransform.setPos({LEFT_POS, BOTTOM_POS});
        actualTransform.setRotation(crTransform.getRotation());
        break;
      // Only scales horiztonally
      case NineSliceTypes::BOTTOM_CENTER:
        actualTransform.setScale({X_SCALE, mBottom});
        actualTransform.setPos({crTransform.getPos().x, BOTTOM_POS});
        actualTransform.setRotation(crTransform.getRotation());
        break;
      // Doesn't Scale
      case NineSliceTypes::BOTTOM_RIGHT:
        actualTransform.setScale({mRight, mBottom});
        actualTransform.setPos({RIGHT_POS, BOTTOM_POS});
        actualTransform.setRotation(crTransform.getRotation());
        break;
    }

    Renderer2D::registerQuad(actualTransform, quad.second, mpTexture, actualTransform.getScale() / 2.0f);
  }
}

SlicedSprite& SlicedSprite::setColor(const lg::Color& crColor)
{
  return *this;
}

void SlicedSprite::movePos(const glm::vec2& crMoveVector)
{

}

SlicedSprite& SlicedSprite::setPos(const glm::vec2& crPos)
{
  return *this;
}

SlicedSprite& SlicedSprite::setSize(const glm::vec2& crSize)
{
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
    quad.second[0].TextCoord = offset / static_cast<glm::vec2>(mpTexture->getSize());

    switch(quad.first)
    {
      case NineSliceTypes::TOP_LEFT:
        quad.second[1].TextCoord = glm::vec2{offset.x + mLeft, offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[2].TextCoord = glm::vec2{offset.x + mLeft, offset.y + mTop} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[3].TextCoord = glm::vec2{offset.x, offset.y + mTop} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::TOP_CENTER:
        quad.second[1].TextCoord = glm::vec2{offset.x + mpTexture->getSize().x - (mRight + 1), offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[2].TextCoord = glm::vec2{offset.x + mpTexture->getSize().x - (mRight + 1), offset.y + mTop} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[3].TextCoord = glm::vec2{offset.x, offset.y + mTop} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::TOP_RIGHT:
        quad.second[1].TextCoord = glm::vec2{offset.x + mRight, offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[2].TextCoord = glm::vec2{offset.x + mRight, offset.y + mTop} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[3].TextCoord = glm::vec2{offset.x, offset.y + mTop} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::MID_LEFT:
        quad.second[1].TextCoord = glm::vec2{offset.x + mLeft, offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[2].TextCoord = glm::vec2{offset.x + mLeft, mpTexture->getSize().y - mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[3].TextCoord = glm::vec2{offset.x, mpTexture->getSize().y - mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::MID_CENTER:
        quad.second[1].TextCoord = glm::vec2{mpTexture->getSize().x - (mRight + 1), offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[2].TextCoord = glm::vec2{mpTexture->getSize().x - (mRight + 1), mpTexture->getSize().y - mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[3].TextCoord = glm::vec2{offset.x, mpTexture->getSize().y - mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::MID_RIGHT:
        quad.second[1].TextCoord = glm::vec2{offset.x + mRight, offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[2].TextCoord = glm::vec2{offset.x + mRight, mpTexture->getSize().y - mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[3].TextCoord = glm::vec2{offset.x, mpTexture->getSize().y - mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::BOTTOM_LEFT:
        quad.second[1].TextCoord = glm::vec2{offset.x + mLeft, offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[2].TextCoord = glm::vec2{offset.x + mLeft, offset.y + mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[3].TextCoord = glm::vec2{offset.x, offset.y + mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::BOTTOM_CENTER:
        quad.second[1].TextCoord = glm::vec2{offset.x + mpTexture->getSize().x - (mRight + 1), offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[2].TextCoord = glm::vec2{offset.x + mpTexture->getSize().x - (mRight + 1), offset.y + mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[3].TextCoord = glm::vec2{offset.x, offset.y + mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        break;
      case NineSliceTypes::BOTTOM_RIGHT:
        quad.second[1].TextCoord = glm::vec2{offset.x + mRight, offset.y} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[2].TextCoord = glm::vec2{offset.x + mRight, offset.y + mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
        quad.second[3].TextCoord = glm::vec2{offset.x, offset.y + mBottom} / static_cast<glm::vec2>(mpTexture->getSize());
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
  
}

glm::vec2 SlicedSprite::getSize() const
{

}

glm::vec2 SlicedSprite::getPos() const
{

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

  // Probably want a delayed update
  if(mpTexture)
  {
    updateTextureCoordinates({0.0f, 0.0f}, mpTexture->getSize());
  }
}