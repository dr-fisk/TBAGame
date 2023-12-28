#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "common.h"
#include "glcommon.h"
#include "renderEngine/texture.h"
#include "resource/textureResource.h"
#include "renderEngine/batchBuffer.h"

enum PrimitiveType
{
  RECTANGLE, 
  TRIANGLE
};

struct VertexData
{
  Vertex QuadVertex;
  Vector2<float> Dimensions;
};

class BatchBuffer;

// Drawable allows drawable items to be held in one container for easy access of render data
class Drawable
{
  public:
    Drawable(){ mRenderId = 0; }
    Drawable(std::shared_ptr<BatchBuffer>& prBatch);
    virtual ~Drawable();
    virtual std::vector<Vertex> getVertex() = 0;
    virtual std::vector<VertexData> getVertexData() = 0;
    virtual TextureResource& getResource() = 0;
    void setRenderId(const uint64_t cRenderId) {mRenderId = cRenderId;}
    uint64_t getRenderId() {return mRenderId;}
  protected:
    uint64_t mRenderId;
    std::shared_ptr<BatchBuffer> mpBatch;
};

#endif