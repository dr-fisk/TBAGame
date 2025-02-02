#ifndef EVENT_SUBSCRIBER_HPP
#define EVENT_SUBSCRIBER_HPP

#include <functional>

#define BIND_EVENT_FN(fn) [this](auto&&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

template <typename T>
class EventSubscriber
{
  public:
    EventSubscriber() = default;
    ~EventSubscriber()
    {
      mUnregister(*this);
    }

    EventSubscriber(const std::function<void(T&)>& crFunc) : mCallback(crFunc)
    {
    }

    void setCallback(const std::function<void(T&)>& crFunc)
    {
      mCallback = crFunc;
    }

    void notify(T& crEvent) const
    {
      if(mCallback)
      {
        mCallback(crEvent);
      }
    }

    void setUnregisterFunc(const std::function<bool(const EventSubscriber<T>&)> cFunc)
    {
      mUnregister = cFunc;
    }
  private:
    std::function<void(T&)> mCallback;
    std::function<bool(const EventSubscriber<T>&)> mUnregister;
};

#endif