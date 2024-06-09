#ifndef I_EVENT_HPP
#define I_EVENT_HPP

#include <string>

#define BIND_EVENT_FN(fn) [this](auto&&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define EVENT_CLASS_SCOPED_TYPE(scope, type) static scope GetStaticType() {  return scope::type; }
#define EVENT_CLASS_SCOPELESS_TYPE(datatype, type) static datatype GetStaticType() { return type; }

template <typename T>
class I_Event
{
  public:
    I_Event() = default;
    I_Event(const T cType, const std::string& crName) : mType(cType), mName(crName) {}
    virtual ~I_Event() = default;
    
    T getType() const
    {
      return mType;
    }

    std::string getName() const
    {
      return mName;
    }

    virtual bool isHandled() const
    {
      return mHandled;
    }
  protected:
    T mType;
    std::string mName;
    bool mHandled = false;
};

#endif