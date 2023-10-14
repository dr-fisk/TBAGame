#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "common.h"
#include "glcommon.h"

enum PrimitiveType
{
  RECTANGLE, 
  TRIANGLE
};

// Drawable allows drawable items to be held in one container for easy access of render data
class Drawable {
  public:
    Drawable(){ mRenderId = 0; }
    virtual ~Drawable(){}
    virtual std::vector<RenderData> getRenderData() = 0;
  protected:
    uint64_t mRenderId;
};

#endif