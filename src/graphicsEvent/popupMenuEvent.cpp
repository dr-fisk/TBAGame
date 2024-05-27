#include "graphicsEvent/popupMenuEvent.hpp"

//! @brief PopupMenuEvent Constructor
//!
//! @param[in] cpSource Component that invoked the event
//!
//! @return PopupMenuEvent Object
template <typename T>
PopupMenuEvent<T>::PopupMenuEvent(T* cpSource) : mpSource(cpSource)
{
}