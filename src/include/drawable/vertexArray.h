#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "common.h"
#include "glcommon.h"
#include "drawable/vertexBuffer.h"
#include "vertexBufferLayout.h"

class VertexArray {
  public:
    VertexArray() = default;
    void genVao();
    ~VertexArray();
    void setVaoAttributes(const VertexBufferLayout &crLayout);
    void bind() const;
    void unbind() const;
  private:
    uint32_t mVaoId;
};

#endif