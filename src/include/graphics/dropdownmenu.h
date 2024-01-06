#ifndef DROP_DOWN_MENU_H
#define DROP_DOWN_MENU_H

#include <memory>
#include <vector>

#include "graphics/button.h"

template <typename T=void *>
class DropDownMenu
{
  public:
    DropDownMenu() = default;
    DropDownMenu(const std::shared_ptr<Button<T>>& crActive, const std::vector<std::shared_ptr<Button<T>>>& crButtons,
                 const Vector2<float>& crPos, const Vector2<float>& crSize);
    ~DropDownMenu() = default;
    void update(const Event& crEvent);
  private:
    enum DropDownMenuState
    {
      DEFAULT_STATE,
      CLICKED_STATE
    };

    std::shared_ptr<Button<T>> mActiveButton;
    std::vector<std::shared_ptr<Button<T>>> mButtons;
    DropDownMenuState mState;
    Vector2<float> mPos;

    void defaultStateHandler(const Event& crEvent);
    void clickedStateHanlder(const Event& crEvent);
    void updateDropDown();
    void showDropDown(const bool cShow);
};

#include "../../graphics/dropdownmenu.c"

#endif