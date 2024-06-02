#ifndef TOGGLE_BUTTON_HPP
#define TOGGLE_BUTTON_HPP

#include "graphics/abstractButton.hpp"

class ToggleButton : public AbstractButton
{
  public:
    ToggleButton();
    ~ToggleButton() = default;
    // void draw() override;
  private:
    virtual void buttonClicked() override;
    void setButtonTexture() override;

    std::shared_ptr<Texture2D> mpCheckedTexture;
    bool mToggled;
};

#endif