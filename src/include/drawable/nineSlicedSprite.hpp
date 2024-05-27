#ifndef NINE_SLICED_SPRITE_HPP
#define NINE_SLICED_SPRITE_HPP

#include <map>

#include "drawable/I_Sprite.hpp"
#include "vertex.hpp"

class SlicedSprite : public I_Sprite
{
  public:
    enum class NineSliceTypes
    {
      TOP_LEFT,      // Doesn't scale
      TOP_CENTER,    // Scales Horizontally
      TOP_RIGHT,     // Doesn't scale
      MID_LEFT,      // Scales Vertically
      MID_CENTER,    // Scales Horizontally and Vertically No center because we have that separate from 9 sliced vector
      MID_RIGHT,     // Scales Vertically
      BOTTOM_LEFT,   // Doesn't scale
      BOTTOM_CENTER, // Scales Horizontally
      BOTTOM_RIGHT,   // Doesn't scale
      NUM_SLICES
    };

    enum class SliceBorder
    {
      TOP,
      LEFT,
      BOTTOM,
      RIGHT
    };

    SlicedSprite();
    ~SlicedSprite() = default;

    void draw(const Transform& crTransform) override;
    SlicedSprite& setColor(const lg::Color& crColor) override;
    void movePos(const glm::vec2& crMoveVector) override;
    SlicedSprite& setPos(const glm::vec2& crPos) override;
    SlicedSprite& setSize(const glm::vec2& crSize) override;
    SlicedSprite& setTexture(const Texture2D& crTexture, const bool cInvert=false) override;
    SlicedSprite& setBox(const Box<glm::vec2>& crBox) override;
    void draw(); // remove
    glm::vec2 getSize() const;
    glm::vec2 getPos() const;

    void setSpecificBorder(const SliceBorder cBorder, const float cSize);
    void setAllBorders(const float cLeft, const float cTop, const float cRight, const float cBottom);
  private:
    void updateTextureCoordinates(const glm::vec2& crOffset, const glm::vec2& crTextureSize) override;
    void setOffset(const NineSliceTypes cType, const glm::vec2& crOffset, glm::vec2& rResult);

    std::map<NineSliceTypes, std::array<Vertex, sNumQuadVerts>> mSlicedQuads;
    float mTop = 1.0f;
    float mBottom = 1.0f;
    float mRight = 1.0f;
    float mLeft = 1.0f;
};

#endif