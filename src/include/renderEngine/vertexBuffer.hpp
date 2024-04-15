#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <vector>
#include <cstdint>

#include "renderEngine/vertexBufferLayout.hpp"

class VertexBuffer
{
  public:
    VertexBuffer() = delete;
    VertexBuffer(const uint32_t cBuffSize, const GLenum cDrawType);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
    void updateVboSubBuffer(const uint32_t cIndex, const uint32_t cBuffSize, void *pBuffer);
    void setLayout(const VertexBufferLayout& crLayout);
    const VertexBufferLayout getLayout() { return mLayout; }
  private:
    uint32_t mVboId;
    uint64_t mLastDataSize;
    VertexBufferLayout mLayout;
};

#endif