#ifndef I_SPRITE_HPP
#define I_SPRITE_HPP

#define GLM_FORCE_CTOR_INIT
#include "drawable/dot.hpp"
#include "shapes/box2D.hpp"
#include "glm/vec2.hpp"
#include "color.hpp"

class I_Sprite : public Dot
{
  public:
    I_Sprite() = default;
    virtual ~I_Sprite() = default;
    virtual I_Sprite& setColor(const lg::Color& crColor) = 0;
    virtual void movePos(const glm::vec2& crMoveVector) = 0;
    virtual I_Sprite& setPos(const glm::vec2& crPos) = 0;
    virtual I_Sprite& setSize(const glm::vec2& crSize) = 0;
    virtual I_Sprite& setBox(const Box<glm::vec2>& crBox) = 0;
    virtual I_Sprite& setTexture(const Texture2D& crTexture, const bool cInvert=false) = 0;
    virtual void draw(const Transform& crTransform) = 0;
  protected:
    virtual void updateTextureCoordinates(const glm::vec2& crOffset, const glm::vec2& crTextureSize) = 0;

    Box2D<float> mBox2D;
    const Texture2D* mpTexture;
};

#endif