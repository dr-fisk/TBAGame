#ifndef FOCUS_EVENT_HPP
#define FOCUS_EVENT_HPP

#include "event/I_Event.hpp"

template <typename T>
class FocusEvent : public I_Event<std::string>
{
  public:
    //! @brief Delete Default Constructor
    FocusEvent() = delete;

    //! @brief Default Destructor
    ~FocusEvent() = default;

    //! @brief Constructor
    //!
    //! @tparam[in] pSrc Source of Event
    FocusEvent(T* pSource, const bool cFocus) : mpSource(pSource), mFocus(cFocus) {}

    EVENT_CLASS_SCOPELESS_TYPE(std::string, "FOCUS");
    T* mpSource;
    bool mFocus = false;
};

#endif