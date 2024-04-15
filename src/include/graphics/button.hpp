#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <functional>

#include "graphics/graphics.hpp"
#include "drawable/sprite.hpp"
#include "drawable/text.hpp"
#include "event/event.hpp"
#include "glm/vec2.hpp"

template <typename T=void *>
class Button : public Graphics
{
  public:
    Button() = delete;
    Button(std::shared_ptr<Font>& prFont, const std::string& crText, std::shared_ptr<RenderEngine>& prRenderEngine,
           const uint8_t cCharSize, const glm::vec2& crPos, const glm::vec2& crSize);
    Button(std::shared_ptr<RenderEngine>& prRenderEngine, const glm::vec2& crPos, const glm::vec2& crSize);
    void setDefaultColor(const lg::Color& crColor);
    void setHoverColor(const lg::Color& crColor);
    void setPressedColor(const lg::Color& crColor);
    void setPos(const glm::vec2& crPos, const bool cCheckIfMouseHovering=true);
    void movePos(const glm::vec2& crMove, const bool cCheckIfMouseHovering=true);
    bool clicked(const Event& crEvent);
    void setSize(const glm::vec2& crSize);
    void onClick(std::function<void(const Button<T>&)> pFunc);
    void disableCallback(const bool cEnable);
    void setRender(const bool cEnable);
    void setId(const int64_t cId);
    int64_t getId() const;
    glm::vec2 getPos() const;
    glm::vec2 getSize() const;
    void setDefaultTexture(const std::shared_ptr<TextureResource>& crpTexture);
    void setHoverTexture(const std::shared_ptr<TextureResource>& crpTexture);
    void setPressedTexture(const std::shared_ptr<TextureResource>& crpTexture);
    void setValue(const T& rValue);
    void setPressedPadding(const glm::vec2& crPadding);
    bool isHover() const;
    bool isPressed() const;
    void setText(const std::string& rText);
    std::string getText() const;
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
    glm::vec2 mPressedPadding;
    int64_t mId;
    T mValue;

    bool isInAABB(const glm::vec2& crPos);
    bool isInAABB(const glm::vec2& crPos, const glm::vec2& crPadding);
    void mouseMoveUpdate(const Event::MouseMoveEvent& crEvent);
    void mouseButtonUpdate(const Event::MouseButtonEvent& crEvent);
    bool mouseButtonRelease(const Event::MouseButtonEvent& crEvent);
    void setTextPos();
    void setButtonTexture();
    void onButtonMoveUpdate(const bool cCheckIfMouseHovering);
};

#include "../../graphics/button.cpp"

#endif