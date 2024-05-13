#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <array>
#include <functional>

#define GLM_FORCE_CTOR_INIT
#include "vertex.hpp"
#include "drawable/dot.hpp"
#include "resource/textureResource.hpp"
#include "shapes/box.hpp"
#include "glm/vec2.hpp"

// Eventually we will deprecate a sprite from knowing it's position.
// This structure allows us to render a sprite directly for easy testing purposes
class Sprite : public Dot
{
  public:
    Sprite();
    Sprite(const Sprite& rSprite);
    Sprite& operator=(const Sprite& rhs);
    Sprite(const Texture2D& crTexture, const Box<glm::vec2>& crBox);
    Sprite(const lg::Color& crColor, const Box<glm::vec2>& crBox);
    ~Sprite();
    const Texture2D& getTexture() const;
    void movePos(const glm::vec2& crMoveVector);
    Sprite& setPos(const glm::vec2& crPos);
    Sprite& setSize(const glm::vec2& crSize);
    Sprite& setTexture(const Texture2D& crTexture, const bool cInvert=false);
    Sprite& setBox(const Box<glm::vec2>& crBox);
    glm::vec2 getSize() const;
    glm::vec2 getPos() const;
    Sprite& setColor(const lg::Color& crColor);
    const Box<glm::vec2>& getBox() const;
    void setLayer(const uint32_t cLayer);
    void draw();
    void draw(const Transform& crTransform);
    Box<glm::vec2> getGlobalBounds(const OrthCamera& crCamera) const;

  private:
    void updateTextureCoordinates(const glm::vec2& crOffset, const glm::vec2& crTextureSize);
    void drawUntexturedSprite2(const Transform& crTransform);
    void drawTexturedSprite2(const Transform& crTransform);
    void drawUntexturedSprite();
    void drawTexturedSprite();
    std::function<void(const Transform&)> RegisterDrawCall(std::function<void(const Transform&)> Callback);

    Box<glm::vec2> mBox;
    glm::vec2 mPrevPos;
    std::array<Vertex, sNumQuadVerts> mVertexes;
    const Texture2D* mpTexture;
    std::function<void()> mDrawFunc;
    std::function<void(const Transform&)> mDrawFunc2;
};

#endif