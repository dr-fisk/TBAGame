#ifndef ACTION_EVENT_HPP
#define ACTION_EVENT_HPP

#include "graphics/component.hpp"

class ActionEvent
{
  public:
    ActionEvent() = delete;
    ~ActionEvent() = default;
    // TODO remove this enum
    enum ActionEventType
    {
      ACTION_OCCURRED
    };

    ActionEvent(Component* pSource, const ActionEventType cType);

    Component* mpSource;
    ActionEventType mType;
};

#endif