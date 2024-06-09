#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <array>
#include <functional>

#include "vertex.hpp"
#include "drawable/I_Sprite.hpp"
#include "shapes/box.hpp"

// Eventually we will deprecate a sprite from knowing it's position.
// This structure allows us to render a sprite directly for easy testing purposes
class Sprite : public I_Sprite
{
  public:
    enum class SpriteDrawMode
    {
      SIMPLE,
      NINE_SLICED
    };

    Sprite();
    Sprite(const Sprite& rSprite);
    Sprite& operator=(const Sprite& rhs);
    Sprite(const Texture2D& crTexture, const Box<glm::vec2>& crBox);
    Sprite(const lg::Color& crColor, const Box<glm::vec2>& crBox);
    ~Sprite() = default;
    const Texture2D& getTexture() const;
    void movePos(const glm::vec2& crMoveVector) override;
    Sprite& setPos(const glm::vec2& crPos) override;
    Sprite& resize(const glm::vec2& crSize) override;
    Sprite& setTransform(const Transform& crTransform) override;
    Sprite& setTexture(const Texture2D& crTexture, const bool cInvert=false) override;
    Sprite& setBox(const Box<glm::vec2>& crBox) override;
    glm::vec2 getSize() const;
    glm::vec2 getPos() const;
    Sprite& setColor(const lg::Color& crColor) override;
    const Box<glm::vec2>& getBox() const;
    void setLayer(const uint32_t cLayer);
    void draw();
    // void draw(const Transform& crTransform) override;
    Box<glm::vec2> getGlobalBounds(const OrthCamera& crCamera) const;
  protected:
    void updateTextureCoordinates(const glm::vec2& crOffset, const glm::vec2& crTextureSize) override;
    void drawUntexturedSprite2(const Transform& crTransform);
    void drawTexturedSprite2(const Transform& crTransform);
    void drawUntexturedSprite();
    void drawTexturedSprite();
    std::function<void(const Transform&)> RegisterDrawCall(std::function<void(const Transform&)> Callback);

    Box<glm::vec2> mBox;
    glm::vec2 mPrevPos;
    std::array<Vertex, sNumQuadVerts> mVertexes;
    std::function<void()> mDrawFunc;
};

#endif