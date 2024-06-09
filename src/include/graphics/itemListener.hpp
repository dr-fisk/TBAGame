#ifndef ITEM_LISTENER_HPP
#define ITEM_LISTENER_HPP

#include "graphicsEvent/componentEventListener.hpp"
#include "graphicsEvent/itemEvent.hpp"

class ItemListener : public ComponentEventListener
{
  public:
    ItemListener() = default;
    ~ItemListener() = default;
    virtual void itemEvent(const ItemEvent& crEvent) = 0;
};

#endif