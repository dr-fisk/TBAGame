#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "common.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class VertexArray {
  public:
    VertexArray(){}
    VertexArray(const uint32_t cNum);
    ~VertexArray();
    void addBuffer(const std::shared_ptr<VertexBuffer> &crpVbo, const VertexBufferLayout &crLayout);
    void bind() const;
    void unbind() const;
  private:
    uint32_t mVaID;
};

#endif