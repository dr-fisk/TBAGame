#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <vector>

#include "net_utility.h"
#include "glcommon.h"

class VertexBuffer {
  public:
    VertexBuffer() = default;
    void genVboBuffer(const uint32_t cBuffSize, const GLenum cDrawType);
    void genVbo();
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
    void updateVboSubBuffer(const uint32_t cIndex, const uint32_t cBuffSize, void *pBuffer);
  private:
    uint32_t mVboId;
    std::vector<uint8_t> mBuffer;
    uint64_t mLastDataSize;
};

#endif