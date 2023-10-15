#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <vector>

#include "glcommon.h"
#include "net_utility.h"

class IndexBuffer {
  public:
    IndexBuffer() = default;
    void genIbo();
    ~IndexBuffer();
    void bind() const;
    void unbind() const;
    void genIboBuffer(const uint32_t cVboSizeBytes, const GLenum cDrawType);
    void updateIboSubBuffer(const uint32_t cIndex, const uint32_t cBuffSize, void *pBuffer);
    void updateIndexBuffer(const uint64_t cNumVertexes);

    /* Function:    getCount
       Description: Returns the IndexBuffer count
       Parameters:  None
       Returns:     uint32_t - IndexBuffer count
    */
    inline uint32_t getCount() const { return mCount; }
  private:
    uint32_t mIboId;
    uint32_t mCount;
    std::vector<uint32_t> mBuffer;
    uint32_t mLastDataSize;
};

#endif