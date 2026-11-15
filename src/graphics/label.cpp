#include "graphics/label.hpp"

Label::Label(const std::string& crText, const Modifier& crModifier, const TextModifier& crTextModifier)
{
  mModifier = crModifier;
  mTextModifier = crTextModifier;
  mText = Text(mTextModifier.getFont(), crText, mTextModifier.getFontSize());
  mSprite.setTransform(mModifier.getTransform());
  mUpdateUI = true;
}

Label::Label(const std::string& crText, const TextModifier& crTextModifier, const Modifier& crModifier)
{
  mModifier = crModifier;
  mTextModifier = crTextModifier;
  mText = Text(mTextModifier.getFont(), crText, mTextModifier.getFontSize());
  mSprite.setTransform(mModifier.getTransform());
  mUpdateUI = true;
}

void Label::draw()
{
  if(mUpdateUI)
  {
    updateUI();
  }

  mSprite.draw();
  mText.draw();
}
   
Label& Label::setVerticalAlign(const VerticalAlign cAlign)
{
  mModifier.setVerticalAlign(cAlign);
  mUpdateUI = true;
  return *this;
}

void Label::verticalAlign()
{
  glm::vec2 labelCenter = mModifier.getPos();
  glm::vec2 labelScale = mModifier.getScale();

  if(mStyleSheet)
  {
    labelCenter = {mStyleSheet.value().mVisualLeft + (mStyleSheet.value().mVisualWidth / 2.0f), mStyleSheet.value().mVisualTop + (mStyleSheet.value().mVisualHeight / 2.0f)};
    labelScale  = {mStyleSheet.value().mVisualWidth, mStyleSheet.value().mVisualHeight};
  }

  switch(mModifier.getVerticalAlign())
  {
    case VerticalAlign::TOP:
    {
      mTextTransform.setOrigin({mTextTransform.getPos().x, labelCenter.y - std::round((labelScale.y / 2.0f))} );
      break;
    }
    case VerticalAlign::CENTER:
    {
      glm::vec2 textSize = mText.getSize();
      mTextTransform.setOrigin({mTextTransform.getPos().x, labelCenter.y - std::round((textSize.y / 2.0f))});
      break;
    }
    case VerticalAlign::BOTTOM:
     {
      glm::vec2 textSize = mText.getSize();
      mTextTransform.setOrigin({mTextTransform.getPos().x, labelCenter.y + std::round((labelScale.y / 2.0f)) - textSize.y});
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
  mModifier.setHorizontalAlign(cAlign);
  mUpdateUI = true;
  return *this;
}

void Label::horizontalAlign()
{
  glm::vec2 labelCenter = mModifier.getPos();
  glm::vec2 labelScale = mModifier.getScale();

  if(mStyleSheet)
  {
    labelCenter = {mStyleSheet.value().mVisualLeft + (mStyleSheet.value().mVisualWidth / 2.0f), mStyleSheet.value().mVisualTop + (mStyleSheet.value().mVisualHeight / 2.0f)};
    labelScale  = {mStyleSheet.value().mVisualWidth, mStyleSheet.value().mVisualHeight};
  }

  switch(mModifier.getHorizontalAlign())
  {
    case HorizontalAlign::LEFT:
    {
      mTextTransform.setOrigin({labelCenter.x - std::round((labelScale.x / 2.0f)), mTextTransform.getPos().y} );
      break;
    }
    case HorizontalAlign::CENTER:
     {
      glm::vec2 textSize = mText.getSize();
      mTextTransform.setOrigin({labelCenter.x - std::round((textSize.x / 2.0f)), mTextTransform.getPos().y});
      break;
     }
    case HorizontalAlign::RIGHT:
    {
      glm::vec2 textSize = mText.getSize();
      mTextTransform.setOrigin({labelCenter.x + std::round((labelScale.x / 2.0f))  - textSize.x, mTextTransform.getPos().y});
      break;
    }
    case HorizontalAlign::CENTER_OUTSIDE_RIGHT:
    {
      glm::vec2 textSize = mText.getSize();
      mTextTransform.setOrigin({mModifier.getPos().x + std::round((mModifier.getWidth() / 2.0f)), mTextTransform.getPos().y});
    }
    case HorizontalAlign::NONE:
      break;
    default:
      break;
  }
}

Label& Label::setFrameSource(const std::shared_ptr<FrameSource> cpFrameSource)
{
  mpTexture = cpFrameSource;
  mSprite.setFrameSource(mpTexture);
  return *this;
}

Label& Label::setBackgroundColor(const lg::Color& crColor)
{
  mSprite.setColor(crColor);
  return *this;
}

Label& Label::movePos(const glm::vec2& crMove)
{
  mModifier.moveTransform(crMove);
  mUpdateUI = true;
  return *this;
}

Label& Label::setPos(const glm::vec2& crPos)
{
  mModifier.setPos(crPos);
  mUpdateUI = true;
  return *this;
}

Label& Label::resize(const glm::vec2& crSize)
{
  mModifier.setScale(crSize);
  mUpdateUI = true;
  return *this;
}

// TODO
Label& Label::setPadding(const glm::vec2&)
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
  alignText();
  mText.setPos(mTextTransform.getPos());
  mUpdateUI = true;
  return *this;
}

const std::string& Label::getString() const
{
  return mText.getString();
}

const Text& Label::getText() const
{
  return mText;
}

Label& Label::setTextColor(const lg::Color& crColor)
{
  mText.setColor(crColor);
  return *this;
}

Label& Label::setTextPosition(const glm::vec2& crPos)
{
  mTextTransform.setOrigin(crPos);
  mUpdateUI = true;
  return *this;
}

Label& Label::setBorder(const float cBorderSize)
{
  mBorderSizePx = std::abs(cBorderSize);

  if(0 == mBorderSizePx)
  {
    mSprite.clearColor();
  }

  mSprite.setBorders(cBorderSize, cBorderSize, cBorderSize, cBorderSize);
  return *this;
}

Label& Label::setBorderColor(const lg::Color& crColor)
{
  mBorderColor = crColor;
  mSprite.fillBorderColor(crColor);
  return *this;
}

bool Label::hasBorder() const
{
  return 0.0f < mBorderSizePx;
}

void Label::updateUI()
{
  mSprite.setTransform(mModifier.getTransform());
  alignText();
  mText.setPos(mTextTransform.getPos());
  mText.updateGeometry();
  mUpdateUI = false;
}

Transform Label::getTextTransform() const
{
  return mTextTransform;
}

TextModifier& Label::getTextModifier()
{
  return mTextModifier;
}

Modifier& Label::getModifier()
{
  return mModifier;
}

Label& Label::setTextModifier(const TextModifier& crTextModifier)
{
  mTextModifier = crTextModifier;
  mText.setFont(mTextModifier.getFont());
  mText.setFontSize(mTextModifier.getFontSize());
  mUpdateUI = true;
  return *this;
}