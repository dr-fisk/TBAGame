#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>
#include <array>
#include <cstdint>

#define GLM_FORCE_CTOR_INIT
#include "vertex.hpp"
#include "resource/font.hpp"
#include "drawable/dot.hpp"
#include "shapes/box.hpp"
#include "glm/vec2.hpp"
#include "renderer/camera.hpp"

class Text : public Dot
{
  public:
    Text();
    Text(const Font& crFont, const std::string& crText, const uint8_t cCharSize=12);
    Text& setString(const std::string& crText);
    const Texture2D& getTexture() const;
    void movePos(const glm::vec2& crMoveVector);
    Text& setPos(const glm::vec2& crPos);
    Text& setFont(const Font& crFont);
    Text& setFontSize(const uint8_t cCharSize);
    Text& setLineWrap(const bool cEnable);
    void insertString(const std::string& crString, const size_t cIndex);
    void appendString(const std::string& crString);
    Text& setColor(const lg::Color &crColor);
    size_t getLength() const;
    glm::vec2 getPos() const;
    std::string& getString();
    const std::string& getString() const;
    glm::vec2 getSize() const;
    glm::vec2 getSize2() const;
    uint8_t getCharSize() const;
    void draw();
    void draw(const Transform& crTransform);
    ~Text();
    Box<glm::vec2> getGlobalBounds(const OrthCamera& crCamera) const;
    std::vector<Box<glm::vec2>> getBoundingBoxes() const;
  private:
    void gridfitText(const glm::vec2& crTopLeft);
    void updateTextureCoordinates(const glm::vec2& crOffset, const glm::vec2& crTextureSize, 
                                std::array<Vertex, sNumQuadVerts>& rVertexes);
    void updateQuadColor(std::array<Vertex, sNumQuadVerts>& rVertexes);
    void gridfitText();

    struct TextVertexData
    {
      glm::vec2 Pos;
      glm::vec2 Size;
      std::array<Vertex, sNumQuadVerts> Vertexes;
    };
  
    const Font* mpFont;
    std::string mText;
    std::vector<TextVertexData> mTextVertexes;
    Box<glm::vec2> mBox;
    glm::vec2 mSize;
    int32_t mLineWrap = -1;
    int32_t mLineSpace;
    uint8_t mCharSize = 12;
    uint16_t mAdvancedWidth;
    int32_t mCapHeight;
    const Texture2D* mpTexture;
    lg::Color mColor = lg::Black;
};

#endif