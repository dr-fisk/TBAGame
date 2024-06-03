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

    // void draw(const Transform& crTransform) override;
    SlicedSprite& setColor(const lg::Color& crColor) override;
    void movePos(const glm::vec2& crMoveVector) override;
    SlicedSprite& setPos(const glm::vec2& crPos) override;
    SlicedSprite& resize(const glm::vec2& crSize) override;
    SlicedSprite& setTransform(const Transform& crTransform) override;
    SlicedSprite& setTexture(const Texture2D& crTexture, const bool cInvert=false) override;
    SlicedSprite& setBox(const Box<glm::vec2>& crBox) override;
    SlicedSprite& setSpecificSliceColor(const NineSliceTypes cSplice, const lg::Color crColor);
    void clearColor();
    void draw();
    glm::vec2 getSize() const;
    glm::vec2 getPos() const;

    void setSpecificBorder(const SliceBorder cBorder, const float cSize);
    void setBorders(const float cLeft, const float cTop, const float cRight, const float cBottom);
    void fillBorderColor(const lg::Color& crColor);
    void removeBorderColor();
  private:
    void updateTextureCoordinates(const glm::vec2& crOffset, const glm::vec2& crTextureSize) override;
    void setOffset(const NineSliceTypes cType, const glm::vec2& crOffset, glm::vec2& rResult);
    void updateGeometry();
    struct SlicedQuadData
    {
      std::array<Vertex, sNumQuadVerts> Vertexes;
      bool UseTexture{false};
      Transform QuadTransform;
    };

    std::map<NineSliceTypes, SlicedQuadData> mSlicedQuads;
    float mTop = 0.0f;
    float mBottom = 0.0f;
    float mRight = 0.0f;
    float mLeft = 0.0f;
};

#endif