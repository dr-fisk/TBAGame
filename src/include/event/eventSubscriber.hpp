#ifndef EVENT_SUBSCRIBER_HPP
#define EVENT_SUBSCRIBER_HPP

#include <functional>

template <typename T>
class EventSubscriber
{
  public:
    EventSubscriber() = default;
    ~EventSubscriber() = default;
    EventSubscriber(const std::function<void(const T&)>& crFunc) : mCallback(crFunc)
    {
    }

    void setCallback(const std::function<void(const T&)>& crFunc)
    {
      mCallback = crFunc;
    }

    void notify(const T& crEvent) const
    {
      if(mCallback)
      {
        mCallback(crEvent);
      }
    }
  private:
    std::function<void(const T&)> mCallback;
};

#endif