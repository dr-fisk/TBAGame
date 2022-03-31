#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "common.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class VertexArray {
  public:
    VertexArray(){}
    VertexArray(uint32_t num);
    ~VertexArray();
    void addBuffer(const std::shared_ptr<VertexBuffer> vb, const VertexBufferLayout &layout);
    void bind() const;
    void unbind() const;
  private:
    uint32_t vaID;
};

#endif