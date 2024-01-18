#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <vector>
#include <memory>

#include "utility/net_utility.h"
#include "renderEngine/vertexBuffer.h"
#include "renderEngine/indexBuffer.h"

class VertexArray
{
  public:
    VertexArray();
    ~VertexArray();
    void setVaoAttributes(const VertexBufferLayout& crLayout);
    void bind() const;
    void unbind() const;
    void addVertexBuffer(const std::shared_ptr<VertexBuffer>& crpVbo);
    void setIndexBuffer(const std::shared_ptr<IndexBuffer>& crpIbo);
  private:
    uint32_t mVaoId;

    std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
    std::shared_ptr<IndexBuffer> mpIndexBuffer;
    uint32_t mVertexBufferIndex;
};

#endif