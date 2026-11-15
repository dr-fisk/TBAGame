#include "graphics/buttonGroup.hpp"

ButtonGroup::ButtonGroup()
{
   mSelectedEventSub.setCallback(BIND_EVENT_FN(ButtonGroup::unselectButtons));
}

ButtonGroup& ButtonGroup::addButton(const std::shared_ptr<ToggleButton> cpButton)
{
  mToggleButtons.push_back(cpButton);
  cpButton->addSelectedEventListener(mSelectedEventSub);
  return *this;
}

void ButtonGroup::unselectButtons(ToggleButton::SelectEvent& rSelectEvent)
{
  int idx = 0;

  for(auto& button : mToggleButtons)
  {
    if(*button != *rSelectEvent.mpSource)
    {
      button->setSelected(false);
    }

    idx ++;
    std::cout << idx << std::endl;
  }
}