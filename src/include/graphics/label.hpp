#ifndef LABEL_HPP
#define LABEL_HPP

#include "graphics/component.hpp"
#include "drawable/sprite.hpp"
#include "drawable/text.hpp"

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
    Label(const Sprite& crSprite, const Text& crText);
    Label(const Text& crText, const Sprite& crSprite);
    ~Label() = default;
    void draw();
    Label& setSprite(const Sprite& crSprite);
    Label& setText(const Text& crText);
    Label& setHorizontalAlign(const HorizontalAlign cAlign);
    Label& setVerticalAlign(const VerticalAlign cAlign);
    Label& setTexture(std::shared_ptr<Texture2D> pTexture);
    Label& setBackgroundColor(const lg::Color& crColor);
    void update();
  private:
    void horizontalAlign();
    void verticalAlign();
    std::function<void()> Register(std::function<void()> Callback);

    Sprite mSprite;
    Text mText;
    Transform mTextTransform;
    std::shared_ptr<Texture2D> mpTexture;
    HorizontalAlign mHorizontalAlign;
    VerticalAlign mVerticalAlign;
};

#endif