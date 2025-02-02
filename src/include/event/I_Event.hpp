#ifndef I_EVENT_HPP
#define I_EVENT_HPP

#include <string>

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

    virtual void setHandled(const bool cHandled)
    {
      mHandled = cHandled;
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