#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include "common.h"
#include "glcommon.h"
#include "drawable/batchBuffer.h"
#include "drawable/shader.h"
#include "drawable/rectangle.h"

class RenderTarget {
    public:
      RenderTarget() = default;
      ~RenderTarget() = default;
      virtual void clear() = 0;
      virtual void display() = 0;
      virtual void draw(Rect &rShape) = 0;
      virtual void draw(const uint64_t cCount) = 0;
      virtual void draw(const std::shared_ptr<VertexBuffer> &crpVbo, const std::shared_ptr<VertexArray> &crpVao,
                        const std::shared_ptr<IndexBuffer> &crpIbo, const VertexBufferLayout &crLayout) = 0;
      virtual uint32_t getWindowHeight() = 0;
      virtual uint32_t getWindowWidth() = 0;
      virtual RenderData createRenderDataBounded(Rect &rShape) = 0;
      virtual void setActive() = 0;
    private:
};

#endif