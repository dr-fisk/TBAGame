#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include <cstdint>

#include "utility/net_utility.h"
#include "event/event.h"
#include "glm/vec2.hpp"

class RenderTarget
{
    public:
      RenderTarget() = default;
      ~RenderTarget() = default;
      virtual void display() = 0;
      virtual void draw(const uint64_t cCount) = 0;
      virtual uint32_t getWindowHeight() = 0;
      virtual uint32_t getWindowWidth() = 0;
      virtual const glm::uvec2& getWindowSize() = 0;
      virtual void setActive() = 0;
      virtual bool pollEvent(Event&) = 0;
    private:
};

#endif