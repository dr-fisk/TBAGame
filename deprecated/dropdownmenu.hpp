#ifndef DROP_DOWN_MENU_HPP
#define DROP_DOWN_MENU_HPP

#include <memory>
#include <vector>
#include <optional>

#include "graphics/component.hpp"
#include "graphics/button.hpp"
#include "glm/vec2.hpp"
#include "graphics/popupMenu.hpp"

//! How to use
//! 1. Provide the Active Button, this will be the button that is displayed when there is no drop down menu
//! 2. Provide a list of buttons that will be shown when drop down menu exists
//! 3. Please ensure Active Button is contained within the Button list as well
//! 4. Optional: Set Callback functions for all buttons, they will be called when that button becomes the active button
//! 5. Alternatively, if you rather check to see which button was clicked, a std::optional will be returned with the
//!    Button ID. Note that the Active Button will be ID 0 and all elements in Vector will be incremented by 1
//!    Map accordingly, or use the function to return Button with given ID
class DropDownMenu : public Component
{
  public:
    enum DisplayOnAction
    {
      HOVER,
      CLICK
    };

    DropDownMenu() = delete;
    DropDownMenu(const uint32_t cActive, const std::vector<std::shared_ptr<Button>>& crButtons,
                 const glm::vec2& crPos, const glm::vec2& crSize);
    ~DropDownMenu() = default;
    std::optional<int32_t> update(const Event& crEvent);
    std::shared_ptr<Button> getButtonByID(const int32_t cId);
    void draw();
    DropDownMenu& addComponent(const std::shared_ptr<Component> cpComponent);
  private:
    void defaultStateHandler(const Event& crEvent);
    std::optional<int32_t> clickedStateHandler(const Event& crEvent);
    void updateDropDown();
    void showDropDown(const bool cShow);

    enum DropDownMenuState
    {
      DEFAULT_STATE,
      CLICKED_STATE
    };

    std::shared_ptr<Button> mActiveButton;
    std::vector<std::shared_ptr<Button>> mButtons;
    std::vector<std::shared_ptr<Component>> mMenuComponents;
    PopupMenu mPopupMenu;
    DropDownMenuState mState;
    glm::vec2 mPos;
    glm::vec2 mSize;
    DisplayOnAction mAction;
};

#endif