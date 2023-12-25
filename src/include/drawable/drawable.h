#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "common.h"
#include "glcommon.h"
#include "drawable/drawable.h"
#include "renderEngine/texture.h"

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

// Drawable allows drawable items to be held in one container for easy access of render data
class Drawable
{
  public:
    Drawable(){ mRenderId = 0; }
    virtual ~Drawable(){}
    virtual std::vector<Vertex> getVertex() = 0;
    virtual std::vector<VertexData> getVertexData() = 0;

    void setRenderId(const uint64_t cRenderId) {mRenderId = cRenderId;}
    uint64_t getRenderId() {return mRenderId;}
  protected:
    uint64_t mRenderId;
    Texture Texture;
};

#endif