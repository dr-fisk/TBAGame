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
    void addBuffer(const VertexBufferLayout &crLayout);
    void bind(const uint32_t cId) const;
    void unbind() const;
    uint32_t getNumVao();
  private:
    static uint8_t smNumVao;
    std::vector<uint32_t> mVertexArrays;
};

#endif