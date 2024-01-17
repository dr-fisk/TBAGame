#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "common.h"
#include "glcommon.h"
#include "renderEngine/texture.h"
#include "resource/textureResource.h"

enum PrimitiveType
{
  RECTANGLE, 
  TRIANGLE
};

// Drawable allows drawable items to be held in one container for easy access of render data
class Drawable
{
  public:
    Drawable(){ mRenderId = 0; mRender = false; mNeedUpdate = false; mRender = true; }
    virtual ~Drawable() = default;
    virtual std::shared_ptr<TextureResource> getResource() = 0;
    virtual bool hasResource() = 0;
    virtual bool textureBounded() = 0;
    virtual Vector2<float> getPos() = 0;
    virtual Vector2<float> getSize() = 0;
    virtual void movePos(const Vector2<float>& crMoveVector) = 0;
    virtual void setPos(const Vector2<float>& crPos) = 0;
    void setRenderId(const uint64_t cRenderId);
    uint64_t getRenderId();
    void setRender(const bool cEnable);
    bool getRender();
    virtual void draw() = 0;
  protected:
    uint64_t mRenderId;
    bool mNeedUpdate;
    bool mRender;
    uint32_t mLayer;
};

#endif