#include "graphics/dropdownmenu.h"

//! @brief Creates DropDownMenu from List of Buttons and Active Button
//!
//! @param crActive  The Active Button to be displayed when DropDown Menu is hidden
//! @param crButtons The list of Buttons to display when DropDown Menus is shown Note: Active Button should be in list
//! @param crPos     The Position of the dropdown menu
//! @param crSize    The size of Buttons
//!
//! @return DropDownMenu Object
template <typename T>
DropDownMenu<T>::DropDownMenu(const std::shared_ptr<Button<T>>& crActive,
                              const std::vector<std::shared_ptr<Button<T>>>& crButtons,
                              const Vector2<float>& crPos, const Vector2<float>& crSize)
{
  mActiveButton = crActive;
  mButtons = crButtons;
  mPos = crPos;
  mState = DEFAULT_STATE;

  uint32_t id = 0;
  mActiveButton->setId(id);
  mActiveButton->setSize(crSize);
  mActiveButton->setPos(crPos);
  mActiveButton->enableCallback(false);
  Vector2<float> nextPos = Vector2<float>(crPos.x, crPos.y + crSize.y);

  id ++;
  for(auto& button : mButtons)
  {
    if(mActiveButton->getId() != button->getId())
    {
      button->setRender(false);
      button->setSize(crSize);
      button->setId(id);
      button->setPos(nextPos, false);
      button->enableCallback(true);
      nextPos.y = nextPos.y + crSize.y;
      id++;
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
      button->enableCallback(true);
      pos.y += button->getSize().y;
    }
  }
}

//! @brief Handles Clicked behavior for dropdown, whether it's hide dropdown or update Active Button
//!
//! @param crEvent Clicked Event to handle
//!
//! @return None 
template <typename T>
void DropDownMenu<T>::clickedStateHanlder(const Event& crEvent)
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
        mActiveButton->enableCallback(false);
        updateDropDown();
        break;
      }
    }
  }
}

//! @brief Handles updating Dropdown Menu given an event
//!
//! @param crEvent Event to process
//!
//! @return True if New Active Item selected false otherwise
template <typename T>
void DropDownMenu<T>::update(const Event& crEvent)
{
  switch(mState)
  {
    case DEFAULT_STATE:
      defaultStateHandler(crEvent);
      break;
    case CLICKED_STATE:
      clickedStateHanlder(crEvent);
      break;
    default:
      break;
  }
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