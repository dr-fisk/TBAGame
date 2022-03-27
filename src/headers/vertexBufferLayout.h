#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include "common.h"

struct VertexBufferElement {
    uint32_t type;
    uint32_t count;
    bool normalized;
};

class VertexBufferLayout {
  public:
    VertexBufferLayout() : stride(0) {}
    ~VertexBufferLayout() {}
    void push(uint32_t count) {
        elements.push_back({GL_FLOAT, count, true});
        stride += sizeof(float) * count;
    }

    inline const std::vector<VertexBufferElement> getElements() const {return elements;}
    inline uint32_t getStride() const {return stride;}
  private:
    std::vector<VertexBufferElement> elements; 
    uint32_t stride;
};

#endif