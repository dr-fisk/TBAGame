#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "common.h"

class IndexBuffer {
  public:
    IndexBuffer() {}
    IndexBuffer(const uint32_t *data, uint32_t count);
    ~IndexBuffer();
    void bind() const;
    void unbind() const;
    void deleteIndexBuffer() const;

    /* Function:    getCount
       Description: Returns the IndexBuffer count
       Parameters:  None
       Returns:     uint32_t - IndexBuffer count
    */
    inline uint32_t getCount() const {return count;}
  private:
    uint32_t indexID;
    uint32_t count;
};

#endif