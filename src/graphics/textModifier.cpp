#include "graphics/textModifier.hpp"

TextModifier& TextModifier::setFont(const Font& crFont)
{
  mpFont = &crFont;
  return *this;
}

TextModifier& TextModifier::setFontSize(const uint8_t cFontSize)
{
  mFontSize = cFontSize;
  return *this;
}

TextModifier& TextModifier::setTextColor(const lg::Color& crColor)
{
  mTextColor = crColor;
  return *this;
}

uint8_t TextModifier::getFontSize() const
{
  return mFontSize;
}

const Font& TextModifier::getFont() const
{
  return *mpFont;
}