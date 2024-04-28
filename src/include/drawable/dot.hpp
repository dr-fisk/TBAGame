#ifndef DOT_HPP
#define DOT_HPP

#include "drawable/drawable.hpp"

class Dot : public Drawable
{
  public:
    Dot();
    virtual ~Dot() = default;
    virtual glm::vec2 getPos() const = 0;
    virtual glm::vec2 getSize() const = 0;
    virtual void movePos(const glm::vec2& crMoveVector) = 0;
    virtual Drawable& setPos(const glm::vec2& crPos) = 0;
    void setRenderId(const uint64_t cRenderId);
    uint64_t getRenderId();
    void setRender(const bool cEnable);
    bool getRender();
  protected:
    uint64_t mRenderId;
    bool mGeometryNeedUpdate;
    bool mRender;
    uint32_t mLayer;
};

#endif