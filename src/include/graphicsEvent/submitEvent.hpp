#ifndef SUBMIT_EVENT_HPP
#define SUBMIT_EVENT_HPP

#include "event/I_Event.hpp"

template <typename T>
class SubmitEvent : public I_Event<std::string>
{
  public:
    //! @brief Delete Default Constructor
    SubmitEvent() = delete;

    //! @brief Default Destructor
    ~SubmitEvent() = default;

    //! @brief Constructor
    //!
    //! @tparam[in] pSrc Source of Event
    SubmitEvent(T* pSource, const std::string& crValue) : mpSource(pSource), mValue(crValue) {}

    EVENT_CLASS_SCOPELESS_TYPE(std::string, "SUBMIT");
    T* mpSource;
    std::string mValue;
};

#endif