#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "drawable/sprite.h"
#include "drawable/text.h"

class Button
{
  public:
    Button() = default;
    Button(std::shared_ptr<Font>& prFont, const std::string& crText, std::shared_ptr<RenderEngine>& prRenderEngine,
           std::shared_ptr<BatchBuffer>& prBatch, const uint8_t cCharSize, const float cTop, const float cLeft,
           const uint32_t cWidth, const uint32_t cHeight);
    void setDefaultColor(const lg::Color& crColor);
    void setHoverColor(const lg::Color& crColor);
    void setPressedColor(const lg::Color& crColor);
    void setPos(const float cLeft, const float cTop);
    void update();
    void setSize(const uint32_t cWidth, const uint32_t cHeight);
    bool buttonPressed();
    ~Button() = default;
  private:
    enum ButtonState
    {
      DEFAULT_STATE,
      HOVER_STATE,
      PRESSED_STATE
    };
    
    std::shared_ptr<Sprite> mBox;
    std::shared_ptr<Text> mText;
    lg::Color mDefaultColor;
    lg::Color mHoverColor;
    lg::Color mPressedColor;
    ButtonState mState;

    bool isInAABB();
};

#endif