#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>
#include <array>
#include <cstdint>

#define GLM_FORCE_CTOR_INIT
#include "vertex.hpp"
#include "resource/font.hpp"
#include "drawable.hpp"
#include "renderEngine/resourceManager.hpp"
#include "shapes/box.hpp"
#include "glm/vec2.hpp"
#include "renderer/camera.hpp"

class Text : public Drawable
{
  public:
    Text() = default;
    Text(std::shared_ptr<Font>& prFont, const std::string& crText, std::shared_ptr<ResourceManager>& prResourceMngr,
         const uint8_t cCharSize, const glm::vec2& crPos,
         const int32_t cLineWrap=-1, const float cLineHeight=1.2f);
    Text(const Font& crFont, const std::string& crText, const uint8_t cCharSize=12);
    Text& setString(const std::string& crText);
    const Texture2D& getTexture() const;
    bool hasResource();
    void movePos(const glm::vec2& crMoveVector);
    Text& setPos(const glm::vec2& crPos);
    Text& setFont(const Font& crFont);
    Text& setFontSize(const uint8_t cCharSize, std::shared_ptr<ResourceManager>& prResourceMngr);
    Text& setLineWrap(const bool cEnable);
    void insertString(const std::string& crString, const size_t cIndex);
    void appendString(const std::string& crString);
    Text& setColor(const lg::Color &crColor);
    size_t getLength() const;
    glm::vec2 getPos() const;
    std::string& getString();
    glm::vec2 getSize() const;
    void draw();
    ~Text();
    Box<glm::vec2> getGlobalBounds(const OrthCamera& crCamera) const;
  private:
      void gridfitText(const glm::vec2& crTopLeft);
      void updateTextureCoordinates(const glm::vec2& crOffset, const glm::vec2& crTextureSize, 
                                  std::array<Vertex, sNumQuadVerts>& rVertexes);
      void updateQuadColor(std::array<Vertex, sNumQuadVerts>& rVertexes);
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
    int32_t mLineWrap = -1;
    int32_t mLineSpace;
    uint8_t mCharSize = 12;
    uint16_t mAdvancedWidth;
    int32_t mCapHeight;
    // std::shared_ptr<TextureResource> mpTexture;
    const Texture2D* mpTexture;
    lg::Color mColor = lg::Black;
};

#endif