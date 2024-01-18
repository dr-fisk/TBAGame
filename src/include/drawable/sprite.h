#ifndef SPRITE_H
#define SPRITE_H

#include "glcommon.h"
#include "drawable/drawable.h"
#include "resource/textureResource.h"
#include "shapes/box.h"
#include "glm/vec2.hpp"

class Sprite : public Drawable
{
  public:
    Sprite() = default;
    Sprite(const std::string& crPath, std::shared_ptr<RenderEngine>& prRenderEngine,
           const glm::vec2& crPos, const glm::vec2& crSize);
    Sprite(const glm::vec2& crPos, const glm::vec2& crSize, const lg::Color& crColor);
    ~Sprite();
    std::shared_ptr<TextureResource> getResource();
    bool hasResource();
    bool textureBounded();
    void movePos(const glm::vec2& crMoveVector);
    void setPos(const glm::vec2& crPos);
    void setSize(const glm::vec2& crSize);
    void setTexture(const std::shared_ptr<TextureResource>& crpTexture, const bool cInvert=false);
    glm::vec2 getSize();
    glm::vec2 getPos();
    void setColor(const lg::Color& crColor);
    Box<glm::vec2>& getBox();
    void setLayer(const uint32_t cLayer);
    void draw();

  private:
    lg::Color mColor;
    std::shared_ptr<TextureResource> mTexture;
    Vertex mVertex;
    Box<glm::vec2> mBox;
};

#endif