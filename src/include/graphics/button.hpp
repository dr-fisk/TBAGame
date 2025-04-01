#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <functional>

#include "graphics/abstractButton.hpp"
#include "graphics/component.hpp"
#include "drawable/sprite.hpp"
#include "graphics/label.hpp"
#include "drawable/text.hpp"
#include "event/event.hpp"
#include "glm/vec2.hpp"

class Button : public AbstractButton
{
  public:
    Button();
    Button(const Modifier& crModifier, const TextModifier& crTextModifier);
    Button& setPos(const glm::vec2& crPos, const bool cCheckIfMouseHovering=true);
    void disableCallback(const bool cEnable);
    Button& setRender(const bool cEnable);
    Button& setId(const int64_t cId);
    int64_t getId() const;
    Button& setPressedPadding(const glm::vec2& crPadding);
    bool isHover() const;
    bool isPressed() const;
    ~Button() = default;
  private:
    void buttonClicked() override;

    glm::vec2 mPressedPadding;
    int64_t mId;
};

#endif