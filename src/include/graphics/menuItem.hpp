#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include "graphics/abstractButton.hpp"

class MenuItem : public AbstractButton
{
  public:
    //! @brief Default Constructor
    MenuItem() = default;

    //! @brief Default Destructor
    virtual ~MenuItem() = default;

    //! @brief Returns nullptr empty vector since Menu Item does not have a list of items
    //! TODO: rework this a little
    //! @return Empty vector
    virtual std::vector<std::shared_ptr<MenuItem>> getMenuItems() const;
  protected:
    //! @brief Performs the action for the Menu Item when it is clicked
    //!        In this case it sets itself back to default state, otherwise hover state will remain
    //! @param[in] crEvent Action Event
    virtual void buttonClicked() override;
  private:
};

#endif