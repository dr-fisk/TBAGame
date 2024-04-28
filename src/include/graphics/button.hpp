#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <functional>

#include "graphics/component.hpp"
#include "drawable/sprite.hpp"
#include "graphics/label.hpp"
#include "drawable/text.hpp"
#include "event/event.hpp"
#include "glm/vec2.hpp"

template <typename T=void *>
class Button : public Component
{
  public:
    Button() = delete;
    Button(const Box<glm::vec2>& crBox);
    Button& setDefaultColor(const lg::Color& crColor);
    Button& setHoverColor(const lg::Color& crColor);
    Button& setPressedColor(const lg::Color& crColor);
    Button& setPos(const glm::vec2& crPos, const bool cCheckIfMouseHovering=true);
    void movePos(const glm::vec2& crMove, const bool cCheckIfMouseHovering=true);
    bool clicked(const Event& crEvent);
    Button& setSize(const glm::vec2& crSize);
    void onClick(std::function<void(const Button<T>&)> pFunc);
    void disableCallback(const bool cEnable);
    Button& setRender(const bool cEnable);
    Button& setId(const int64_t cId);
    int64_t getId() const;
    glm::vec2 getPos() const;
    glm::vec2 getSize() const;
    Button& setDefaultTexture(const std::shared_ptr<Texture2D>& crpTexture);
    Button& setHoverTexture(const std::shared_ptr<Texture2D>& crpTexture);
    Button& setPressedTexture(const std::shared_ptr<Texture2D>& crpTexture);
    Button& setValue(const T& rValue);
    Button& setPressedPadding(const glm::vec2& crPadding);
    bool isHover() const;
    bool isPressed() const;
    Button& setText(const Text& crText);
    Button& setString(const std::string& crString);
    Button& setTextColor(const lg::Color &crColor);
    std::string& getString();
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
    
    Sprite mBox;
    Text mText;
    Label mLabel;
    std::shared_ptr<Texture2D> mpDefaultTexture;
    std::shared_ptr<Texture2D> mpHoverTexture;
    std::shared_ptr<Texture2D> mpPressedTexture;
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