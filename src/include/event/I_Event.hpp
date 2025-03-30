#ifndef I_EVENT_HPP
#define I_EVENT_HPP

#include <string>

#define EVENT_CLASS_SCOPED_TYPE(scope, type) static scope GetStaticType() {  return scope::type; }
#define EVENT_CLASS_SCOPELESS_TYPE(datatype, type) static datatype GetStaticType() { return type; }

template <typename T>
class I_Event
{
  public:
    //! @brief Default Constructor
    I_Event(const T cEventType)
    {
      mType = cEventType;
    }

    //! @brief Default Destructor
    virtual ~I_Event() = default;
    
    //! @brief Sets if the event was handled
    //!
    //! @return None 
    void setHandled()
    {
      mHandled = true;
    }

    //! @brief Sets the stop propogating flag, dispatchers will not notify any listeners once set
    //!
    //! @return None
    void stopPropagating()
    {
      mStopPropagating = true;
    }

    //! @brief Sets whether propagation should bubble (down->up)
    //!
    //! @param cBubble Should/Should not bubble
    //!
    //! @return None 
    void bubbleEvent(const bool cBubble)
    {
      mBubbleEvent = cBubble;
    }

    //! @brief Checks if event was handled
    //!
    //! @return true if handled
    //! @return false if not handled 
    bool isHandled() const
    {
      return mHandled;
    }

    //! @brief Check if event should stop propagating
    //!
    //! @return true if event should stop propagating
    //! @return false otherwise
    bool stopEvent() const
    {
      return mStopPropagating;
    }

    //! @brief Check if event should be bubbled
    //!
    //! @return true if event should bubble
    //! @return false if event should not bubble
    bool shouldBubble() const
    {
      return mBubbleEvent;
    }

    T GetEventType()
    {
      return mType;
    }
  protected:
    bool mHandled = false;
    bool mStopPropagating = false;
    bool mBubbleEvent = false;
    T mType;
};

#endif