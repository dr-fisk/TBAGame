#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "common.h"

class VertexBuffer {
  public:
    VertexBuffer() {}
    VertexBuffer(const uint32_t cNumVbo);
    ~VertexBuffer();
    void bind(const uint32_t cId) const;
    void unbind() const;
    void updateBoundedBufferData(const void *cpData, const uint32_t cSize, const GLenum cDrawType);
  private:
    std::vector<uint32_t> mBuffers;
    uint64_t mLastDataSize;
};

#endif