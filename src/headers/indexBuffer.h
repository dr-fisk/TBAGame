#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "common.h"

class IndexBuffer {
  public:
    IndexBuffer() {}
    IndexBuffer(const uint32_t cNumIbo, const uint32_t *cpData, const uint32_t cCount);
    ~IndexBuffer();
    void bind(const uint32_t cId) const;
    void unbind() const;
    void updateBoundedBufferData(const void *cpData, const uint32_t cCount, const GLenum cDrawType);

    /* Function:    getCount
       Description: Returns the IndexBuffer count
       Parameters:  None
       Returns:     uint32_t - IndexBuffer count
    */
    inline uint32_t getCount() const {return mCount;}
  private:
    std::vector<uint32_t> mIndexBuffers;
    uint32_t mLastDataSize;
    //TODO: Update to be more dynamic
    uint32_t mCount;
};

#endif