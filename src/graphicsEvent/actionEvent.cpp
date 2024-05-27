#include "graphicsEvent/actionEvent.hpp"

//! @brief ActionEvent Constructor
//!
//! @param[in] cpSource Component that invoked the event
//! @param[in] cType    Type of action TODO: Determine if wanted
//!
//! @return ActionEvent Object
template <typename T>
ActionEvent<T>::ActionEvent(T* pSource, const ActionEventType cType) : mpSource(pSource), mType(cType)
{
}