#include "input/keyboardEvent.hpp"

namespace LestRenderEngine
{

KeyboardEvent::KeyboardEvent(const LestRenderEngineEvents cType, const std::string& crKeyboardEventName,
  const int32_t cKey, const int32_t cScancode, const int32_t cAction, const int32_t cMods) :
  I_Event(cType, crKeyboardEventName), mKey(cKey), mScancode(cScancode), mAction(cAction), mMods(cMods)
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


KeyboardPressEvent::KeyboardPressEvent() 
: KeyboardEvent(LestRenderEngineEvents::KEY_PRESS, "KeyPress", 0, 0, 0, 0)
{
}

KeyboardPressEvent::KeyboardPressEvent(const int32_t cKey, const int32_t cScancode, const int32_t cAction,
                                       const int32_t cMods)
: KeyboardEvent(LestRenderEngineEvents::KEY_PRESS, "KeyPress", cKey, cScancode, cAction, cMods)
{
}

KeyboardReleaseEvent::KeyboardReleaseEvent() 
: KeyboardEvent(LestRenderEngineEvents::KEY_RELEASE, "KeyRelease", 0, 0, 0, 0)
{
}

KeyboardReleaseEvent::KeyboardReleaseEvent(const int32_t cKey, const int32_t cScancode, const int32_t cAction,
                                           const int32_t cMods)
: KeyboardEvent(LestRenderEngineEvents::KEY_RELEASE, "KeyRelease", cKey, cScancode, cAction, cMods)
{
}

}