#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <array>

#define GLM_FORCE_CTOR_INIT
#include "glcommon.hpp"
#include "drawable/drawable.hpp"
#include "resource/textureResource.hpp"
#include "shapes/box.hpp"
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
    void draw2(glm::vec2 prevpos, const double cDeltaTime);
    Box<glm::vec2> getGlobalBounds(const OrthCamera& crCamera);

  private:
    void updateTextureCoordinates(const glm::vec2& crOffset, const glm::vec2& crTextureSize);

    lg::Color mColor;
    std::shared_ptr<TextureResource> mTexture;
    Box<glm::vec2> mBox;
    glm::vec2 mPrevPos;
    std::array<Vertex, sNumQuadVerts> mVertexes;
};

#endif