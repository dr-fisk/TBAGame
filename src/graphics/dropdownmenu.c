#include "graphics/dropdownmenu.h"

//! @brief Creates DropDownMenu from List of Buttons and Active Button
//!
//! @param crActiveIdx  The Active Button to be displayed when DropDown Menu is hidden
//! @param crButtons The list of Buttons to display when DropDown Menus is shown Note: Active Button should be in list
//! @param crPos     The Position of the dropdown menu
//! @param crSize    The size of Buttons
//!
//! @return DropDownMenu Object
template <typename T>
DropDownMenu<T>::DropDownMenu(const uint32_t cActiveIdx,
                              const std::vector<std::shared_ptr<Button<T>>>& crButtons,
                              const Vector2<float>& crPos, const Vector2<float>& crSize)
{
  // Add future throw
  mActiveButton = crButtons[cActiveIdx];
  mButtons = crButtons;
  mPos = crPos;
  mState = DEFAULT_STATE;

  uint32_t id = 0;

  for(auto& button : mButtons)
  {
    button->setId(id);
    id ++;
  }

  mActiveButton->setId(id);
  mActiveButton->setSize(crSize);
  mActiveButton->setPos(crPos);
  mActiveButton->disableCallback(true);
  Vector2<float> nextPos = Vector2<float>(crPos.x, crPos.y + crSize.y);

  for(auto& button : mButtons)
  {
    if(mActiveButton->getId() != button->getId())
    {
      button->setRender(false);
      button->setSize(crSize);
      button->setPos(nextPos, false);
      button->disableCallback(false);
      nextPos.y = nextPos.y + crSize.y;
    }
  }
}

//! @brief Handles the Default State of the Dropdown Menu checking for when the Active Button gets clicked
//!
//! @param crEvent Event to handle
//!
//! @return None
template <typename T>
void DropDownMenu<T>::defaultStateHandler(const Event& crEvent)
{
  if(mActiveButton->clicked(crEvent))
  {
    std::cout << "BAM\n";
    mState = CLICKED_STATE;
    showDropDown(true);
  }
}

//! @brief Updates the Dropdown Menu Button Positions
//!
//! @return None
template <typename T>
void DropDownMenu<T>::updateDropDown()
{
  Vector2<float> pos = mActiveButton->getPos();
  pos.y += mActiveButton->getSize().y;

  for(auto& button : mButtons)
  {
    if(mActiveButton->getId() != button->getId())
    {
      button->setPos(pos, false);
      button->setRender(false);
      button->disableCallback(false);
      pos.y += button->getSize().y;
    }
  }
}

//! @brief Handles Clicked behavior for dropdown, whether it's hide dropdown or update Active Button
//!
//! @param crEvent Clicked Event to handle
//!
//! @return Optional value, it will be set if a valid Button click has occurred
template <typename T>
std::optional<int32_t> DropDownMenu<T>::clickedStateHanlder(const Event& crEvent)
{
  for(auto& button : mButtons)
  {
    if(button->clicked(crEvent))
    {
      mState = DEFAULT_STATE;
      if(mActiveButton->getId() == button->getId())
      {
        showDropDown(false);
        break;
      }
      else
      {
        button->setPos(mActiveButton->getPos());
        mActiveButton = button;
        mActiveButton->disableCallback(true);
        updateDropDown();
        return std::optional<int32_t>(mActiveButton->getId());
      }
    }
  }

  return std::optional<int32_t>();
}

//! @brief Handles updating Dropdown Menu given an event
//!
//! @param crEvent Event to process
//!
//! @return Optional value, it will be set if a valid Button click has occurred
template <typename T>
std::optional<int32_t> DropDownMenu<T>::update(const Event& crEvent)
{
  switch(mState)
  {
    case DEFAULT_STATE:
      defaultStateHandler(crEvent);
      break;
    case CLICKED_STATE:
      return clickedStateHanlder(crEvent);
    default:
      break;
  }
  return std::optional<int32_t>();
}

//! @brief Show/Hide the Dropdown Menu
//!
//! @param cShow Show/Hide Dropdown Menu
//!
//! @return None 
template <typename T>
void DropDownMenu<T>::showDropDown(const bool cShow)
{
  for(auto& button : mButtons)
  {
    if(mActiveButton->getId() != button->getId())
    {
      button->setRender(cShow);
    }
  }
}

//! @brief Searches for Button that correlates to the ID
//! 
//! @param cId ID of Button
//!
//! @return Button if found, nullptr otherwise 
template <typename T>
std::shared_ptr<Button<T>> DropDownMenu<T>::getButtonByID(const int32_t cId)
{
  for(const auto& button : mButtons)
  {
    if(button->getId() == cId)
    {
      return button;
    }
  }

  return nullptr;
}