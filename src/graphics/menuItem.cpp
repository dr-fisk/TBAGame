#include "graphics/menuItem.hpp"

//! @brief Default Constructor
//!
//! @return MenuItem object
MenuItem::MenuItem()
{
}

//! @brief Returns nullptr empty vector since Menu Item does not have a list of items
//! TODO: rework this a little
//! @return Empty vector
std::vector<std::shared_ptr<MenuItem>> MenuItem::getMenuItems() const
{
  return std::vector<std::shared_ptr<MenuItem>>();
}

//! @brief Performs the action for the Menu Item when it is clicked
//!        In this case it sets itself back to default state, otherwise hover state will remain
//! @param[in] crEvent Action Event
//!
//! @return None
void MenuItem::buttonClicked()
{
  mState = DEFAULT_STATE;
}