#include "input/keyboardEvent.hpp"

namespace lre
{

KeyboardEvent::KeyboardEvent(const LestRenderEngineEvents cEventType, const int32_t cKey, const int32_t cScancode,
  const int32_t cAction, const int32_t cMods) :
  I_Event(cEventType), mKey(cKey), mScancode(cScancode), mAction(cAction), mMods(cMods)
{ 
}

int32_t KeyboardEvent::getKey() const
{
  return mKey;
}

int32_t KeyboardEvent::getScancode() const
{
  return mScancode;
}

int32_t KeyboardEvent::getAction() const
{
  return mAction;
}

int32_t KeyboardEvent::getMods() const
{
  return mMods;
}

KeyboardEvent& KeyboardEvent::operator=(const KeyboardEvent& rhs)
{
  if(this == &rhs)
  {
    return *this;
  }

  mKey = rhs.getKey();
  mAction = rhs.getAction();
  mScancode = rhs.getScancode();
  mMods = rhs.getScancode();

  return *this;
}

KeyboardPressEvent::KeyboardPressEvent() 
: KeyboardEvent(LestRenderEngineEvents::KEY_PRESS, 0, 0, 0, 0)
{
}

KeyboardPressEvent::KeyboardPressEvent(const int32_t cKey, const int32_t cScancode, const int32_t cAction,
                                       const int32_t cMods)
: KeyboardEvent(LestRenderEngineEvents::KEY_PRESS, cKey, cScancode, cAction, cMods)
{
}

KeyboardReleaseEvent::KeyboardReleaseEvent() 
: KeyboardEvent(LestRenderEngineEvents::KEY_RELEASE, 0, 0, 0, 0)
{
}

KeyboardReleaseEvent::KeyboardReleaseEvent(const int32_t cKey, const int32_t cScancode, const int32_t cAction,
                                           const int32_t cMods)
: KeyboardEvent(LestRenderEngineEvents::KEY_RELEASE, cKey, cScancode, cAction, cMods)
{
}

}