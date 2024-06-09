#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include "graphics/abstractButton.hpp"

class MenuItem : public AbstractButton
{
  public:
    MenuItem();
    virtual ~MenuItem() = default;
    virtual std::vector<std::shared_ptr<MenuItem>> getMenuItems() const;
  protected:
    virtual void buttonClicked() override;
  private:
};

#endif