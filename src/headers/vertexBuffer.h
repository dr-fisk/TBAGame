#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "common.h"

class VertexBuffer {
  public:
    VertexBuffer() {}
    VertexBuffer(const void *data, uint32_t size);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
  private:
    uint32_t bufID;
};

#endif