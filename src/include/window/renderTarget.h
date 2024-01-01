#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include <cstdint>

#include "utility/net_utility.h"

class RenderTarget
{
    public:
      RenderTarget() = default;
      ~RenderTarget() = default;
      virtual void clear() = 0;
      virtual void display() = 0;
      virtual void draw(const uint64_t cCount) = 0;
      virtual uint32_t getWindowHeight() = 0;
      virtual uint32_t getWindowWidth() = 0;
      virtual void setActive() = 0;
      virtual void setKeyCallback() = 0;
      virtual bool isKeyPressed(const int cKey) = 0;
    private:
};

#endif