#ifndef ACTION_LISTENER_HPP
#define ACTION_LISTENER_HPP

#include "graphicsEvent/componentEventListener.hpp"
#include "graphicsEvent/actionEvent.hpp"

template <typename T>
class ActionListener : public ComponentEventListener
{
  public:
    ActionListener() = default;
    ~ActionListener() = default;
    virtual void performAction(const ActionEvent<T>& crEvent) = 0;
};

#endif