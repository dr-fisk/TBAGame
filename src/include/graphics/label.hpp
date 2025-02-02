#ifndef LABEL_HPP
#define LABEL_HPP

#include "graphics/component.hpp"
#include "drawable/text.hpp"
#include "drawable/nineSlicedSprite.hpp"

// TODO move into subfolder
#include "graphics/modifier.hpp"
#include "graphics/textModifier.hpp"

class Label : public Component
{
  public:
    //! @brief  Default constructor
    Label() = default;

    //! @brief Constructs label with given constraints
    //!
    //! @param[in] crText Text to display
    //! @param[in] crModifier Layout Modifier 
    //! @param[in] crTextModifier Text Modifier
    Label(const std::string& crText, const Modifier& crModifier, const TextModifier& crTextModifier);

    //! @brief Constructs label with given constraints
    //!
    //! @param[in] crText Text to display
    //! @param[in] crTextModifier Text Modifier
    //! @param[in] crModifier Layout Modifier
    Label(const std::string& crText, const TextModifier& crTextModifier, const Modifier& crModifier);

    //! @brief Default destructor
    ~Label() = default;

    //! @brief Draws the label
    //!
    //! @return None
    void draw();

    //! @brief Sets the horizontal alignment of the text
    //!
    //! @param[in] cAlign Horizontal alignment
    //! 
    //! @return Label reference to chain calls 
    Label& setHorizontalAlign(const HorizontalAlign cAlign);

    //! @brief Sets the vertical alignment of the text
    //!
    //! @param[in] cAlign Vertical alignment
    //! 
    //! @return Label reference to chain calls
    Label& setVerticalAlign(const VerticalAlign cAlign);

    //! @brief Sets the texture of the sprite associated with the label
    //!
    //! @param[in] pTexture Texture to set
    //!
    //! @return Label reference to chain calls
    Label& setTexture(std::shared_ptr<Texture2D> pTexture);

    //! @brief Sets the backgrounds color of the sprite
    //!        Note: If sprite is textured this won't be used
    //! 
    //! @param[in] crColor Color
    //!
    //! @return Label reference to chain calls
    Label& setBackgroundColor(const lg::Color& crColor);

    //! @brief Move label by specified amount
    //!
    //! @param[in] crMove Amount to move label
    //!
    //! @return Label reference to chain calls
    Label& movePos(const glm::vec2& crMove) override;

    //! @brief Sets the Label Position
    //!
    //! @param[in] crPos Position
    //!
    //! @return Label reference to chain calls
    Label& setPos(const glm::vec2& crPos) override;

    //! @brief Sets the Label Size
    //!
    //! @param[in] crSize Size
    //!
    //! @return Label reference to chain calls
    Label& resize(const glm::vec2& crSize) override;

    Label& setPadding(const glm::vec2& crPadding) override;

    //! @brief Sets the Label String
    //!
    //! @param[in] crString New Label String
    //!
    //! @return Label reference to chain calls
    Label& setString(const std::string& crString);

    //! @brief Sets the fill color of the text displayed on Label
    //!
    //! @param[in] crColor Fill Color
    //!
    //! @return Label reference to chain calls
    Label& setTextColor(const lg::Color& crColor);

    //! @brief Sets the position of Text directly
    //!        Note: This will be overwritten if the Horizontal and Vertical alignment is not set to None
    //!
    //! @param[in] crPos Position
    //!
    //! @return Label reference to chain calls
    Label& setTextPosition(const glm::vec2& crPos);

    //! @brief Sets the border size of the label.
    //!
    //! This function sets the border size in pixels for all four sides (top, bottom, left, and right).
    //!
    //! @param[in] cBorderSize The size of the border in pixels. Must be non-negative
    //! (absolute value is taken if negative).
    //!
    //! @details
    //! - If `cBorderSize` is zero, the sprite's color is cleared.
    //! - Otherwise, sets all four borders to the given `cBorderSize`.
    //!
    //! @return A reference to this Label object, enabling fluent interface usage.
    Label& setBorder(const float cBorderSize);

    //! @brief Sets the border color of the label.
    //!
    //! @param[in] crColor The new border color to be set.
    //!
    //! @return A reference to this Label object, enabling fluent interface usage.
    Label& setBorderColor(const lg::Color& crColor);

    //! @brief Gets the string displayed on the Label
    //!
    //! @return Label String const reference
    const std::string& getString() const;
    
    //! @brief Returns a constant reference to the label's text object.
    //!
    //! @return A constant reference to the `Text` object associated with this label.
    const Text& getText() const;
    
    //! @brief Checks if the label has a border enabled.
    //!
    //! @return `true` if `mBorderSizePx > 0.0f`, otherwise `false`.
    bool hasBorder() const;

    //! @brief Updates the UI elements of the label, including positioning and transformations.
    //!
    //! @return None
    void updateUI() override;
  private:
    //! @brief Aligns the text horizontally on the associated sprite
    //!
    //! @return None
    void horizontalAlign();

    //! @brief Aligns the text vertically on the associated sprite
    //!
    //! @return None
    void verticalAlign();
    
    //! @brief Aligns Label Text to it's horizontal and vertical alignment
    //!
    //! @return None
    void alignText();

    SlicedSprite mSprite;
    Text mText;
    Transform mTextTransform;
    std::shared_ptr<Texture2D> mpTexture;
    Modifier mModifier;
    TextModifier mTextModifier;
    float mBorderSizePx = 0.0f;
    lg::Color mBorderColor;
};

#endif