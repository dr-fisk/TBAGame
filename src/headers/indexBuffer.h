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
    inline uint32_t getCount() const {return count;}
  private:
    uint32_t indexID;
    uint32_t count;
};

#endif