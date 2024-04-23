#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <array>

#define GLM_FORCE_CTOR_INIT
#include "vertex.hpp"
#include "drawable/drawable.hpp"
#include "resource/textureResource.hpp"
#include "shapes/box.hpp"
#include "glm/vec2.hpp"

class Sprite : public Drawable
{
  public:
    Sprite() = default;

    Sprite(const Texture2D& crTexture, const Box<glm::vec2>& crBox);
    Sprite(const lg::Color& crColor, const Box<glm::vec2>& crBox);
    ~Sprite();
    const Texture2D& getTexture() const;
    bool hasResource();
    void movePos(const glm::vec2& crMoveVector);
    Sprite& setPos(const glm::vec2& crPos);
    Sprite& setSize(const glm::vec2& crSize);
    Sprite& setTexture(const std::shared_ptr<TextureResource>& crpTexture, const bool cInvert=false);
    Sprite& setTexture(const Texture2D& crTexture, const bool cInvert=false);
    Sprite& setBox(const Box<glm::vec2>& crBox);
    glm::vec2 getSize() const;
    glm::vec2 getPos() const;
    Sprite& setColor(const lg::Color& crColor);
    const Box<glm::vec2>& getBox() const;
    void setLayer(const uint32_t cLayer);
    void draw();
    Box<glm::vec2> getGlobalBounds(const OrthCamera& crCamera) const;

  private:
    void updateTextureCoordinates(const glm::vec2& crOffset, const glm::vec2& crTextureSize);

    lg::Color mColor;
    std::shared_ptr<TextureResource> mTexture;
    Box<glm::vec2> mBox;
    glm::vec2 mPrevPos;
    std::array<Vertex, sNumQuadVerts> mVertexes;
    const Texture2D* mpTexture;
};

#endif