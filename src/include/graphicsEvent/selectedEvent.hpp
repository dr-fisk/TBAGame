#ifndef SELECTED_EVENT_HPP
#define SELECTED_EVENT_HPP

#include "event/I_Event.hpp"

template <typename T>
class SelectedEvent : public I_Event<std::string>
{
  public:
    //! @brief Delete Default Constructor
    SelectedEvent() = delete;

    //! @brief Default Destructor
    ~SelectedEvent() = default;

    SelectedEvent(T* pSource) : I_Event("SELECT"), mpSource(pSource){}

    EVENT_CLASS_SCOPELESS_TYPE(std::string, "SELECT");

    T* mpSource;
};

#endif