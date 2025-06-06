#ifndef LABEL_HPP
#define LABEL_HPP

#include "graphics/component.hpp"
#include "drawable/text.hpp"
#include "drawable/nineSlicedSprite.hpp"

class Label : public Component
{
  public:
    enum class HorizontalAlign
    {
      LEFT,
      CENTER,
      RIGHT,
      NONE
    };

    enum class VerticalAlign
    {
      TOP,
      CENTER,
      BOTTOM,
      NONE
    };

    Label() = default;
    Label(const Text& crText);
    Label(const Transform& crTranform, const Text& crText);
    Label(const Text& crText, const Transform& crTranform);
    ~Label() = default;
    void draw();
    Label& setText(const Text& crText);
    Label& setHorizontalAlign(const HorizontalAlign cAlign);
    Label& setVerticalAlign(const VerticalAlign cAlign);
    Label& setTexture(std::shared_ptr<Texture2D> pTexture);
    Label& setBackgroundColor(const lg::Color& crColor);
    Label& movePos(const glm::vec2& crMove) override;
    Label& setPos(const glm::vec2& crPos) override;
    Label& resize(const glm::vec2& crSize) override;
    Label& setPadding(const glm::vec2& crPadding) override;
    Label& setString(const std::string& crString);
    Label& setTextColor(const lg::Color& crColor);
    Label& setTextPosition(const glm::vec2& crPos);
    Label& setBorder(const float cBorderSize);
    Label& setBorderColor(const lg::Color& crColor);
    const std::string& getString() const;
    bool hasBorder() const;
    void updateUI() override;
  private:
    void horizontalAlign();
    void verticalAlign();
    void alignText();

    SlicedSprite mSprite;
    Text mText;
    Transform mTextTransform;
    std::shared_ptr<Texture2D> mpTexture;
    HorizontalAlign mHorizontalAlign = HorizontalAlign::NONE;
    VerticalAlign mVerticalAlign = VerticalAlign::NONE;
    float mBorderSizePx = 0.0f;
    lg::Color mBorderColor;
};

#endif