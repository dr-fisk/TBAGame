#ifndef SPRITE_H
#define SPRITE_H

#include "glcommon.h"
#include "drawable/drawable.h"
#include "resource/textureResource.h"
#include "shapes/box.h"

class Sprite : public Drawable
{
  public:
    Sprite() = default;
    Sprite(const std::string& crPath, std::shared_ptr<RenderEngine>& prRenderEngine,
           const Vector2<float>& crPos, const Vector2<float>& crSize);
    Sprite(const Vector2<float>& crPos, const Vector2<float>& crSize, const lg::Color& crColor);
    ~Sprite();
    std::shared_ptr<TextureResource> getResource();
    bool hasResource();
    bool textureBounded();
    void movePos(const Vector2<float>& crMoveVector);
    void setPos(const Vector2<float>& crPos);
    void setSize(const Vector2<float>& crSize);
    void setTexture(const std::shared_ptr<TextureResource>& crpTexture);
    Vector2<float> getSize();
    Vector2<float> getPos();
    void setColor(const lg::Color& crColor);
    Box<float>& getBox();
    void setLayer(const uint32_t cLayer);
    void draw();

  private:
    lg::Color mColor;
    std::shared_ptr<TextureResource> mTexture;
    Vertex mVertex;
    Box<float> mBox;
};

#endif