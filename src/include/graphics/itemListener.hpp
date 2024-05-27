#ifndef ITEM_LISTENER_HPP
#define ITEM_LISTENER_HPP

#include "event/eventListener.hpp"
#include "graphicsEvent/itemEvent.hpp"

class ItemListener : public EventListener
{
  public:
    ItemListener() = default;
    ~ItemListener() = default;
    virtual void itemEvent(const ItemEvent& crEvent) = 0;
};

#endif