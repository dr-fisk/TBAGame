#ifndef TEXT_MODIFIER_HPP
#define TEXT_MODIFIER_HPP

#include "color.hpp"
#include "resource/font.hpp"

class TextModifier
{
  public:
    //! @brief Default Constructor
    TextModifier() = default;

    //! @brief Default Destructor
    ~TextModifier() = default;

    //! @brief Sets Font
    //!
    //! @param[in] crFont Font (Keep Loaded in Memory)
    //!
    //! @return TextModifier Reference
    TextModifier& setFont(const Font& crFont);

    //! @brief Sets Font Size
    //!
    //! @param[in] cFontSize Font Size 
    //!
    //! @return TextModifier Reference
    TextModifier& setFontSize(const uint8_t cFontSize);

    //! @brief Sets Text Color
    //!
    //! @param[in] crColor Color 
    //!
    //! @return TextModifier Reference
    TextModifier& setTextColor(const lg::Color& crColor);

    //! @brief Gets Font Size
    //!
    //! @return Font Size
    uint8_t getFontSize() const;

    //! @brief Gets the Font
    //!
    //! @return Font
    const Font& getFont() const;
  private:
    lg::Color mTextColor;
    uint8_t mFontSize;
    const Font* mpFont;
    //TODO bold, italics, other stuff
};

#endif