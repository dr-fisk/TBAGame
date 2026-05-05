#ifndef I_SPRITE_HPP
#define I_SPRITE_HPP

#define GLM_FORCE_CTOR_INIT
#include "drawable/dot.hpp"
#include "shapes/rect.hpp"
#include "glm/vec2.hpp"
#include "color.hpp"
#include "resource/frameSource.hpp"

#include <memory>

class I_Sprite : public Dot
{
  public:
    I_Sprite() = default;
    virtual ~I_Sprite() = default;
    virtual I_Sprite& setColor(const lg::Color& crColor) = 0;
    virtual void movePos(const glm::vec2& crMoveVector) = 0;
    virtual I_Sprite& setPos(const glm::vec2& crPos) = 0;
    virtual I_Sprite& resize(const glm::vec2& crSize) = 0;
    virtual I_Sprite& setTransform(const Transform& crTransform) = 0;
    virtual I_Sprite& setBox(const Rect<float>& crBox) = 0;
    virtual I_Sprite& setFrameSource(const std::shared_ptr<FrameSource> cpFrameSource, const bool cInvert=false) = 0;
    virtual I_Sprite& update(const float cDt) = 0;

    // virtual void draw(const Transform& crTransform) = 0;
  protected:
    Rect<float> mBox2D;
    std::shared_ptr<FrameSource> mpFrameSource;
    Transform mTransform;
};

#endif