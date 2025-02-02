#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP

#include "event/eventSubscriber.hpp"

#include <vector>
#include <functional>

class I_EventDispatcher
{
  public:
    virtual ~I_EventDispatcher() = default;
};

template<typename T>
class EventDispatcher : public I_EventDispatcher
{
  public:
    EventDispatcher() = default;
    ~EventDispatcher() = default;

    void registerToEvent(const EventSubscriber<T>& crSub)
    {
      mObservers.push_back(&crSub);
    }

    void notify(T& crEvent) const
    {
      for(auto& observer : mObservers)
      {
        observer->notify(crEvent);

        if(crEvent.isHandled())
        {
          break;
        }
      }
    }

    void unregisterFromEvent(const EventSubscriber<T>& crSub)
    {
      for(auto itr = mObservers.begin(); itr != mObservers.end();)
      {
        if(*itr == &crSub)
        {
          itr = mObservers.erase(itr);
        }
        else
        {
          itr ++;
        }
      }
    }

  private:
    std::vector<const EventSubscriber<T>*> mObservers;
};

#endif