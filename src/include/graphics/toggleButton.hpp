#ifndef TOGGLE_BUTTON_HPP
#define TOGGLE_BUTTON_HPP

#include "graphics/abstractButton.hpp"

class ToggleButton : public AbstractButton
{
  public:
    ToggleButton();
    ~ToggleButton() = default;
    void draw() override;
  private:
    virtual void buttonClicked() override;

    bool mToggled;
    Sprite mToggleSprite;
};

#endif