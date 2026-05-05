#ifndef EVENT_PUBLISHER_HPP
#define EVENT_PUBLISHER_HPP

#include <functional>
#include <list>

#include "event/event.hpp"
#include "event/eventSubcriber.hpp"

template <typename Value>
class EventPublisher
{
  public:
    EventPublisher() = default;
    ~EventPublisher() = default;
    void subscribe(const EventSubscriber& rSubscriber, std::function<void(Value)> Callback);
    void unsubscribe(const EventSubscriber& rSubscriber);
    void publish();
  private:
    struct Listener
    {
      const EventSubscriber* Subscriber;
      std::function<void(Value)> CallbackFunc;
    };

    std::list<Listener> mEventManager;
};

#endif