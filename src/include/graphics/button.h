#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "drawable/sprite.h"
#include "drawable/text.h"
#include "event/event.h"

class Button
{
  public:
    Button() = default;
    Button(std::shared_ptr<Font>& prFont, const std::string& crText, std::shared_ptr<RenderEngine>& prRenderEngine,
           std::shared_ptr<BatchBuffer>& prBatch, const uint8_t cCharSize, const Vector2<float>& crPos,
           const Vector2<float>& crSize);
    void setDefaultColor(const lg::Color& crColor);
    void setHoverColor(const lg::Color& crColor);
    void setPressedColor(const lg::Color& crColor);
    void setPos(const Vector2<float>& crPos);
    void handleEvents(const Event& crEvent);
    void setSize(const Vector2<float>& crSize);
    void setCallback(std::function<void(void)> pFunc);
    ~Button() = default;
  private:
    enum ButtonState
    {
      DEFAULT_STATE,
      HOVER_STATE
    };
    
    std::shared_ptr<Sprite> mBox;
    std::shared_ptr<Text> mText;
    lg::Color mDefaultColor;
    lg::Color mHoverColor;
    lg::Color mPressedColor;
    ButtonState mState;
    std::function<void(void)> mCallback;

    bool isInAABB(const Vector2<float>& crPos);
    void mouseMoveUpdate(const Event::MouseMoveEvent& crEvent);
    void mouseButtonUpdate(const Event::MouseButtonEvent& crEvent);
    void mouseButtonRelease(const Event::MouseButtonEvent& crEvent);
    // void noEventUpdate();
};

#endif