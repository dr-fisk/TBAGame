#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <functional>

#include "graphics/graphics.h"
#include "drawable/sprite.h"
#include "drawable/text.h"
#include "event/event.h"

template <typename T=void *>
class Button : public Graphics
{
  public:
    Button() = default;
    Button(std::shared_ptr<Font>& prFont, const std::string& crText, std::shared_ptr<RenderEngine>& prRenderEngine,
           const uint8_t cCharSize, const Vector2<float>& crPos, const Vector2<float>& crSize);
    Button(std::shared_ptr<RenderEngine>& prRenderEngine, const Vector2<float>& crPos, const Vector2<float>& crSize);
    void setDefaultColor(const lg::Color& crColor);
    void setHoverColor(const lg::Color& crColor);
    void setPressedColor(const lg::Color& crColor);
    void setPos(const Vector2<float>& crPos, const bool cCheckIfMouseHovering=true);
      void movePos(const Vector2<float>& crMove, const bool cCheckIfMouseHovering=true);
    bool clicked(const Event& crEvent);
    void setSize(const Vector2<float>& crSize);
    void onClick(std::function<void(const Button<T>&)> pFunc);
    void disableCallback(const bool cEnable);
    void setRender(const bool cEnable);
    void setId(const int64_t cId);
    int64_t getId() const;
    Vector2<float> getPos() const;
    Vector2<float> getSize() const;
    void setDefaultTexture(const std::shared_ptr<TextureResource>& crpTexture);
    void setHoverTexture(const std::shared_ptr<TextureResource>& crpTexture);
    void setPressedTexture(const std::shared_ptr<TextureResource>& crpTexture);
    void setValue(const T& rValue);
    void setPressedPadding(const Vector2<float>& crPadding);
    bool isHover() const;
    bool isPressed() const;
    T getValue() const;
    void draw();
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
    std::shared_ptr<TextureResource> mDefaultTexture;
    std::shared_ptr<TextureResource> mHoverTexture;
    std::shared_ptr<TextureResource> mPressedTexture;
    lg::Color mDefaultColor;
    lg::Color mHoverColor;
    lg::Color mPressedColor;
    ButtonState mState;
    std::function<void(const Button<T>&)> mCallback;
    bool mCallbackDisabled;
    Vector2<float> mPressedPadding;
    int64_t mId;
    T mValue;

    bool isInAABB(const Vector2<float>& crPos);
    bool isInAABB(const Vector2<float>& crPos, const Vector2<float>& crPadding);
    void mouseMoveUpdate(const Event::MouseMoveEvent& crEvent);
    void mouseButtonUpdate(const Event::MouseButtonEvent& crEvent);
    bool mouseButtonRelease(const Event::MouseButtonEvent& crEvent);
    void setTextPos();
    void setButtonTexture();
    void onButtonMoveUpdate(const bool cCheckIfMouseHovering);
};

#include "../../graphics/button.c"

#endif