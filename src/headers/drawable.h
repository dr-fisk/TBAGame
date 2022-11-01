#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "common.h"
#include "rectangle.h"

// Drawable allows drawable items to be held in one container for easy access of render data
class Drawable {
  public:
    Drawable(){}
    virtual ~Drawable(){}
    virtual std::vector<RenderData> getRenderData() = 0;
  private:
};

#endif