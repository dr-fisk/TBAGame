#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "common.h"

class VertexBuffer {
  public:
    VertexBuffer() {}
    VertexBuffer(const void *cpData, const uint32_t cSize);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
  private:
    uint32_t mBuffID;
};

#endif