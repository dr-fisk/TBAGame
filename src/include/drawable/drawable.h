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
    virtual std::shared_ptr<TextureResource> getResource() = 0;
    virtual bool needUpdate() = 0;
    virtual void getVertex(std::vector<Vertex>& rBatchVertexes, uint32_t& rVertexIdx) = 0;
    virtual bool hasResource() = 0;
    virtual bool textureBounded() = 0;
    virtual void movePos(float cX, float cY) = 0;
    void setRenderId(const uint64_t cRenderId);
    uint64_t getRenderId();
  protected:
    uint64_t mRenderId;
    std::shared_ptr<BatchBuffer> mpBatch;
    bool mNeedUpdate;
};

#endif