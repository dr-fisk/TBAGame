#ifndef ACTION_EVENT_HPP
#define ACTION_EVENT_HPP

#include "graphics/component.hpp"

template <typename T>
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

    ActionEvent(T* pSource, const ActionEventType cType);

    T* mpSource;
    ActionEventType mType;
};

#include "../../graphicsEvent/actionEvent.cpp"

#endif