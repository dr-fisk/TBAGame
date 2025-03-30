#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP

#include "event/eventSubscriber.hpp"

#include <vector>
#include <functional>
#include <iostream>

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

    void notify(T& rEvent) const
    {
      if(rEvent.shouldBubble())
      {
        for(auto itr = mObservers.rbegin(); itr != mObservers.rend(); ++itr)
        {
          (*itr)->notify(rEvent);

          if(rEvent.stopEvent())
          {
            break;
          }
        }
      }
      else
      {
        for(auto& observer : mObservers)
        {
          observer->notify(rEvent);

          if(rEvent.stopEvent())
          {
            break;
          }
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

    std::vector<const EventSubscriber<T>*> getObservers() const
    {
      return mObservers;
    }

    void insert(const std::vector<const EventSubscriber<T>*>& crObservers)
    {
      mObservers.insert(mObservers.end(), crObservers.begin(), crObservers.end());
    }
  private:
    std::vector<const EventSubscriber<T>*> mObservers;
};

#endif