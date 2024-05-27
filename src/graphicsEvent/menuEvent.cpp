#include "graphicsEvent/menuEvent.hpp"

//! @brief MenuEvent Constructor
//!
//! @param[in] cpSource Component that invoked the event
//!
//! @return MenuEvent Object
MenuEvent::MenuEvent(Component* pSource) : mpSource(pSource)
{
}