#include "graphics/label.hpp"

//! @brief Constructs a label with specified text object
//!
//! @param[in] crText Text to set to label
//!
//! @return Label Object 
Label::Label(const Text& crText)
{
  mSprite.setBox({mTransform.getPos(), mTransform.getScale()});
  mText = crText;
  mHorizontalAlign = HorizontalAlign::NONE;
  mVerticalAlign = VerticalAlign::NONE;
  mUpdateUI = true;
}

//! @brief Constructs a label with specified transform and text
//!
//! @param[in] crTranform Transform to set
//! @param[in] crText     crText Text to set to label
//!
//! @return Label Object
Label::Label(const Transform& crTransform, const Text& crText)
{
  mSprite.setBox({{0, 0}, crTransform.getScale()});
  mTransform = crTransform;
  mText = crText;
  mHorizontalAlign = HorizontalAlign::NONE;
  mVerticalAlign = VerticalAlign::NONE;
  mUpdateUI = true;
}

//! @brief Constructs a label with specified transform and text
//!
//! @param[in] crText     crText Text to set to label
//! @param[in] crTranform Transform to set
//!
//! @return Label Object
Label::Label(const Text& crText, const Transform& crTranform)
{
  mSprite.setBox({{0, 0}, crTranform.getScale()});
  mTransform = crTranform;
  mText = crText;
  mUpdateUI = true;
}

//! @brief Draws the label
//!
//! @return None
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

//! @brief Sets the text on the Label
//!
//! @param[in] crText Text to set on label
//!
//! @return Label reference to chain calls
Label& Label::setText(const Text& crText)
{
  mText = crText;
  mUpdateUI = true;
  return *this;
}

//! @brief Sets the vertical alignment of the text
//!
//! @param[in] cAlign Vertical alignment
//! 
//! @return Label reference to chain calls 
Label& Label::setVerticalAlign(const VerticalAlign cAlign)
{
  mVerticalAlign = cAlign;
  mUpdateUI = true;
  return *this;
}

//! @brief Aligns the text vertically on the associated sprite
//!
//! @return None
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

//! @brief Sets the horizontal alignment of the text
//!
//! @param[in] cAlign Horizontal alignment
//! 
//! @return Label reference to chain calls 
Label& Label::setHorizontalAlign(const HorizontalAlign cAlign)
{
  mHorizontalAlign = cAlign;
  mUpdateUI = true;
  return *this;
}

//! @brief Aligns the text horizontally on the associated sprite
//!
//! @return None
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

//! @brief Sets the texture of the sprite associated with the label
//!
//! @param[in] pTexture Texture to set
//!
//! @return Label reference to chain calls
Label& Label::setTexture(std::shared_ptr<Texture2D> pTexture)
{
  mpTexture = pTexture;
  mSprite.setTexture(*mpTexture);
  return *this;
}

//! @brief Sets the backgrounds color of the sprite
//!        Note: If sprite is textured this won't be used 
//! @param[in] crColor Color
//!
//! @return Label reference to chain calls
Label& Label::setBackgroundColor(const lg::Color& crColor)
{
  mSprite.setColor(crColor);
  return *this;
}

//! @brief Move label by specified amount
//!
//! @param[in] crMove Amount to move label
//!
//! @return Label reference to chain calls
Label& Label::movePos(const glm::vec2& crMove)
{
  mTransform += crMove;
  mUpdateUI = true;
  return *this;
}

//! @brief Sets the Label Position
//!
//! @param[in] crPos Position
//!
//! @return Label reference to chain calls
Label& Label::setPos(const glm::vec2& crPos)
{
  mTransform.setPos(crPos);
  mUpdateUI = true;
  return *this;
}

//! @brief Sets the Label Size
//!
//! @param[in] crSize Size
//!
//! @return Label reference to chain calls
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

//! @brief Aligns Label Text to it's horizontal and vertical alignment
//!
//! @return None
void Label::alignText()
{
  horizontalAlign();
  verticalAlign();
}

//! @brief Sets the Label String
//!
//! @param[in] crString New Label String
//!
//! @return Label reference to chain calls
Label& Label::setString(const std::string& crString)
{
  mText.setString(crString);
  mUpdateUI = true;
  return *this;
}

//! @brief Gets the string displayed on the Label
//!
//! @return Label String
const std::string& Label::getString() const
{
  return mText.getString();
}

//! @brief Sets the fill color of the text displayed on Label
//!
//! @param[in] crColor Fill Color
//!
//! @return Label reference to chain calls
Label& Label::setTextColor(const lg::Color& crColor)
{
  mText.setColor(crColor);
  return *this;
}

//! @brief Sets the position of Text directly
//!        Note: This will be overwritten if the Horizontal and Vertical alignment is not set to None
//!
//! @param[in] crPos Position
//!
//! @return Label reference to chain calls
Label& Label::setTextPosition(const glm::vec2& crPos)
{
  mTextTransform.setPos(crPos);
  mUpdateUI = true;
  return *this;
}
