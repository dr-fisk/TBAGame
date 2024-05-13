#include "graphics/label.hpp"

Label::Label(const Text& crText)
{
  mSprite.setBox({mTransform.getPos(), mTransform.getScale()});
  mText = crText;
  mHorizontalAlign = HorizontalAlign::NONE;
  mVerticalAlign = VerticalAlign::NONE;
  mUpdateUI = true;
}

Label::Label(const Transform& crTranform, const Text& crText)
{
  mSprite.setBox({{0, 0}, crTranform.getScale()});
  mTransform = crTranform;
  mText = crText;
  mHorizontalAlign = HorizontalAlign::NONE;
  mVerticalAlign = VerticalAlign::NONE;
  mUpdateUI = true;
}

Label::Label(const Text& crText, const Transform& crTranform)
{
  mSprite.setBox({{0, 0}, crTranform.getScale()});
  mTransform = crTranform;
  mText = crText;
  mUpdateUI = true;
}

void Label::draw()
{
  if(mUpdateUI)
  {
    alignText();
    mUpdateUI = false;
  }

  mSprite.draw(mTransform);
  mText.draw(mTextTransform);
}

Label& Label::setText(const Text& crText)
{
  mText = crText;
  mUpdateUI = true;
  return *this;
}

Label& Label::setVerticalAlign(const VerticalAlign cAlign)
{
  mVerticalAlign = cAlign;
  mUpdateUI = true;
  return *this;
}
void Label::verticalAlign()
{
  switch(mVerticalAlign)
  {
    case VerticalAlign::TOP:
    {
      glm::vec2 textSize = mText.getSize();
      glm::vec2 labelCenter = mTransform.getPos();
      glm::vec2 labelScale = mTransform.getScale();
      mTextTransform.setPos({mTextTransform.getPos().x, labelCenter.y - (labelScale.y / 2.0f)} );
      break;
    }
    case VerticalAlign::CENTER:
    {
      glm::vec2 textSize = mText.getSize();
      glm::vec2 labelCenter = mTransform.getPos();
      mTextTransform.setPos({mTextTransform.getPos().x, labelCenter.y - (textSize.y / 2.0f)});
      break;
    }
    case VerticalAlign::BOTTOM:
     {
      glm::vec2 textSize = mText.getSize();
      glm::vec2 labelCenter = mTransform.getPos();
      glm::vec2 labelScale = mTransform.getScale();
      mTextTransform.setPos({mTextTransform.getPos().x, labelCenter.y + (labelScale.y / 2.0f) - textSize.y});
      break;
     }
    case VerticalAlign::NONE:
      break;
    default:
      break;
  }
}

Label& Label::setHorizontalAlign(const HorizontalAlign cAlign)
{
  mHorizontalAlign = cAlign;
  mUpdateUI = true;
  return *this;
}

void Label::horizontalAlign()
{
  switch(mHorizontalAlign)
  {
    case HorizontalAlign::LEFT:
    {
      glm::vec2 textSize = mText.getSize();
      glm::vec2 labelCenter = mTransform.getPos();
      glm::vec2 labelScale = mTransform.getScale();
      mTextTransform.setPos({labelCenter.x - (labelScale.x / 2.0f), mTextTransform.getPos().y} );
      break;
    }
    case HorizontalAlign::CENTER:
     {
      glm::vec2 textSize = mText.getSize();
      glm::vec2 labelCenter = mTransform.getPos();
      mTextTransform.setPos({labelCenter.x - (textSize.x / 2.0f), mTextTransform.getPos().y});
      break;
     }
    case HorizontalAlign::RIGHT:
    {
      glm::vec2 textSize = mText.getSize();
      glm::vec2 labelCenter = mTransform.getPos();
      glm::vec2 labelScale = mTransform.getScale();
      mTextTransform.setPos({labelCenter.x + (labelScale.x / 2.0f)  - textSize.x, mTextTransform.getPos().y} );
      break;
    }
    case HorizontalAlign::NONE:
      break;
    default:
      break;
  }
}

Label& Label::setTexture(std::shared_ptr<Texture2D> pTexture)
{
  mpTexture = pTexture;
  mSprite.setTexture(*mpTexture);
  return *this;
}

Label& Label::setBackgroundColor(const lg::Color& crColor)
{
  mSprite.setColor(crColor);
  return *this;
}

Label& Label::movePos(const glm::vec2& crMove)
{
  mTransform += crMove;
  mUpdateUI = true;
  return *this;
}

Label& Label::setPos(const glm::vec2& crPos)
{
  mTransform.setPos(crPos);
  mUpdateUI = true;
  return *this;
}

Label& Label::resize(const glm::vec2& crSize)
{
  mTransform.setScale(crSize);
  mUpdateUI = true;
  return *this;
}

// TODO
Label& Label::setPadding(const glm::vec2& crPadding)
{
  return *this;
}

void Label::alignText()
{
  horizontalAlign();
  verticalAlign();
}

Label& Label::setString(const std::string& crString)
{
  mText.setString(crString);
  mUpdateUI = true;
  return *this;
}

const std::string& Label::getString() const
{
  return mText.getString();
}

Label& Label::setTextColor(const lg::Color& crColor)
{
  mText.setColor(crColor);
  return *this;
}

Label& Label::setTextPosition(const glm::vec2& crPos)
{
  mTextTransform.setPos(crPos);
  mUpdateUI = true;
  return *this;
}
