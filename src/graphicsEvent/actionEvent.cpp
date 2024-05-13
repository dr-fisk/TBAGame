#include "graphicsEvent/actionEvent.hpp"

ActionEvent::ActionEvent(Component* pSource, const ActionEventType cType) : mpSource(pSource), mType(cType)
{
}