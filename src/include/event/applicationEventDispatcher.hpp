#ifndef APPLICATION_EVENT_DISPATCHER_HPP
#define APPLICATION_EVENT_DISPATCHER_HPP

#include "event/eventDispatcher.hpp"

#include <functional>
#include <map>
#include <memory>
#include <iostream>

namespace LestRenderEngine
{
// Strengths of this Event handler, it ensures type safety and will deliver right event type to function callback
// Downside currently is all the temporary consructions of classes to get type
template <typename Key>
class ApplicationEventDispatcher
{
  public:
    ApplicationEventDispatcher() = default;
    ~ApplicationEventDispatcher() = default;

    template<typename T>
    void addEventDispatcher()
    {
      mDispatcher.emplace(T::GetStaticType(), std::make_unique<EventDispatcher<T>>());
    }

    template<typename T>
    void attach(const EventSubscriber<T>& crSub)
    {
      static_cast<EventDispatcher<T>*>(mDispatcher.at(T::GetStaticType()).get())->registerToEvent(crSub);
    }

    template<typename T>
    void dispatch(T& crEvent)
    {
      static_cast<EventDispatcher<T>*>(mDispatcher.at(T::GetStaticType()).get())->notify(crEvent);
    }

    template<typename T>
    void detach(const EventSubscriber<T>& crSub)
    {
      static_cast<EventDispatcher<T>*>(mDispatcher.at(T::GetStaticType()).get())->unregisterFromEvent(crSub);
    }
  private:
    std::map<Key, std::unique_ptr<I_EventDispatcher>> mDispatcher;
};

}

#endif