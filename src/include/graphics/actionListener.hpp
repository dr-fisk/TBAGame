#ifndef ACTION_LISTENER_HPP
#define ACTION_LISTENER_HPP

#include "event/eventListener.hpp"
#include "graphicsEvent/actionEvent.hpp"

class ActionListener : public EventListener
{
  public:
    ActionListener() = default;
    ~ActionListener() = default;
    virtual void performAction(const ActionEvent& crEvent) = 0;
};

#endif