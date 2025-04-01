#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP

#include <cstdint>

#include "utility/net_utility.hpp"
#include "glm/vec2.hpp"

class RenderTarget
{
    public:
      RenderTarget() = default;
      ~RenderTarget() = default;
      virtual void display() = 0;
      virtual uint32_t getWindowHeight() = 0;
      virtual uint32_t getWindowWidth() = 0;
      virtual const glm::uvec2& getWindowSize() = 0;
      virtual void setActive() = 0;
    private:
};

#endif