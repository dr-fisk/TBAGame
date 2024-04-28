#include "graphics/label.hpp"

Label::Label(const Sprite& crSprite, const Text& crText)
{
  mSprite = crSprite;
  mText = crText;
  mTextTransform.setScale({1, 1});
  mHorizontalAlign = HorizontalAlign::NONE;
  mVerticalAlign = VerticalAlign::NONE;
  mExtraUpdate = Register([=](){return update();});
  horizontalAlign();
  verticalAlign();
}

Label::Label(const Text& crText, const Sprite& crSprite)
{
  mSprite = crSprite;
  mText = crText;
  mTextTransform.setScale({1, 1});
  horizontalAlign();
  verticalAlign();
}

void Label::draw()
{
  mSprite.draw(mTransform);
  mText.draw(mTextTransform);
}

Label& Label::setSprite(const Sprite& crSprite)
{
  mSprite = crSprite;
  horizontalAlign();
  verticalAlign();
  return *this;
}

Label& Label::setText(const Text& crText)
{
  mText = crText;
  mTextTransform.setScale({1, 1});
  horizontalAlign();
  verticalAlign();
  return *this;
}

Label& Label::setVerticalAlign(const VerticalAlign cAlign)
{
  mVerticalAlign = cAlign;
  verticalAlign();
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
      mTextTransform.setPos({mTextTransform.getPos().x, mTransform.getPos().y});
      break;
    default:
      break;
  }
}

Label& Label::setHorizontalAlign(const HorizontalAlign cAlign)
{
  mHorizontalAlign = cAlign;
  horizontalAlign();
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
      mTextTransform.setPos({mTransform.getPos().y, mTextTransform.getPos().y});
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

std::function<void()> Label::Register(std::function<void()> Callback)
{
  return Callback;
}

void Label::update()
{
  horizontalAlign();
  verticalAlign();
}