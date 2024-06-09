#ifndef ITEM_EVENT_HPP
#define ITEM_EVENT_HPP

#include "event/event.hpp"

class ItemEvent
{
  public:
    enum class ItemEventType
    {
      SELECTED,
      DESELECTED
    };

    ItemEvent() = delete;
    ItemEvent(const ItemEventType cEventType);
    ~ItemEvent() = default;

    ItemEventType mType;
};

#endif