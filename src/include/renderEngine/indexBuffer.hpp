#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include <vector>
#include <cstdint>

class IndexBuffer
{
  public:
    IndexBuffer() = delete;
    IndexBuffer(const uint32_t cNumIndices, const GLenum cDrawType);
    ~IndexBuffer();
    void bind() const;
    void unbind() const;
    void updateIboSubBuffer(const uint32_t cIndex, const uint32_t cBuffSize, void *pBuffer);
    void updateIndexBuffer(const uint64_t cNumVertexes);

    //! @brief Returns the IndexBuffer count
    //!
    //! @return IndexBuffer count
    inline uint32_t getCount() const { return mCount; }
  private:
    uint32_t mIboId;
    uint32_t mCount;
    uint32_t mLastDataSize;
};

#endif