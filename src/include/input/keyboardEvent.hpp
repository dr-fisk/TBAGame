#ifndef KEYBOARD_EVENT_HPP
#define KEYBOARD_EVENT_HPP

#include "event/I_Event.hpp"
#include "event/lestRenderEngineEvent.hpp"

namespace lre
{
  class KeyboardEvent : public I_Event<LestRenderEngineEvents>
  {
    public:
      KeyboardEvent() = delete;
      virtual ~KeyboardEvent() = default;
      int32_t getKey() const;
      int32_t getScancode() const;
      int32_t getAction() const;
      int32_t getMods() const;
      KeyboardEvent& operator=(const KeyboardEvent& rhs);
    protected:
      KeyboardEvent(const LestRenderEngineEvents cEventType, const int32_t cKey, const int32_t cScancode,
        const int32_t cAction, const int32_t cMods);
      int32_t mKey;
      int32_t mScancode;
      int32_t mAction;
      int32_t mMods;
  };

  class KeyboardPressEvent : public KeyboardEvent
  {
    public:
      KeyboardPressEvent();
      KeyboardPressEvent(const int32_t cKey, const int32_t cScancode, const int32_t cAction, const int32_t cMods);
      ~KeyboardPressEvent() = default;

      EVENT_CLASS_SCOPED_TYPE(LestRenderEngineEvents, KEY_PRESS)
  };

  class KeyboardReleaseEvent : public KeyboardEvent
  {
    public:
      KeyboardReleaseEvent();
      KeyboardReleaseEvent(const int32_t cKey, const int32_t cScancode, const int32_t cAction, const int32_t cMods);
      ~KeyboardReleaseEvent() = default;
  
      EVENT_CLASS_SCOPED_TYPE(LestRenderEngineEvents, KEY_RELEASE)
  };
}

#endif