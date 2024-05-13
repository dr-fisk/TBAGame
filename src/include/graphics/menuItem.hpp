#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include "graphics/abstractButton.hpp"

class MenuItem : public AbstractButton
{
  public:
    MenuItem();
    virtual ~MenuItem() = default;
    std::vector<std::shared_ptr<MenuItem>> getMenuItems() const;
    virtual void performAction(const ActionEvent& crEvent) override;
  protected:
    std::vector<std::shared_ptr<MenuItem>> mMenuItemList;
  private:
};

#endif