#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "common.h"

class IndexBuffer {
  public:
    IndexBuffer() {}
    IndexBuffer(const uint32_t *cpData, const uint32_t cCount);
    ~IndexBuffer();
    void bind() const;
    void unbind() const;

    /* Function:    getCount
       Description: Returns the IndexBuffer count
       Parameters:  None
       Returns:     uint32_t - IndexBuffer count
    */
    inline uint32_t getCount() const {return mCount;}
  private:
    uint32_t mIndexID;
    uint32_t mCount;
};

#endif