#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>
#include <array>
#include <cstdint>

#define GLM_FORCE_CTOR_INIT
#include "vertex.hpp"
#include "resource/font.hpp"
#include "drawable.hpp"
#include "renderEngine/renderEngine.hpp"
#include "shapes/box.hpp"
#include "glm/vec2.hpp"
#include "renderer/camera.hpp"

class Text : public Drawable
{
  public:
    Text() = default;
    Text(std::shared_ptr<Font>& prFont, const std::string& crText, std::shared_ptr<RenderEngine>& prRenderEngine,
         const uint8_t cCharSize, const glm::vec2& crPos,
         const int32_t cLineWrap=-1, const float cLineHeight=1.2f);
    void gridfitText(const glm::vec2& crTopLeft);
    void updateText(const std::string& crText);
    std::shared_ptr<TextureResource> getResource();
    bool hasResource();
    void movePos(const glm::vec2& crMoveVector);
    void setPos(const glm::vec2& crPos);
    void setFont(std::shared_ptr<Font>& prFont);
    void setFontSize(const uint8_t cCharSize, std::shared_ptr<RenderEngine>& prRenderEngine);
    void setLineWrap(const bool cEnable);
    glm::vec2 getPos() const;
    std::string getText() const;
    glm::vec2 getSize() const;
    void draw();
    ~Text();
    void updateTextureCoordinates(const glm::vec2& crOffset, const glm::vec2& crTextureSize, 
                                  std::array<Vertex, sNumQuadVerts>& rVertexes);
    Box<glm::vec2> getGlobalBounds(const OrthCamera& crCamera) const;
  private:
    struct TextVertexData
    {
      glm::vec2 Pos;
      glm::vec2 Size;
      std::array<Vertex, sNumQuadVerts> Vertexes;
    };
  
    std::shared_ptr<Font> mpFont;
    std::string mText;
    std::vector<TextVertexData> mTextVertexes;
    Box<glm::vec2> mBox;
    int32_t mLineWrap = -1;
    int32_t mLineSpace = 1.2f;
    uint8_t mCharSize;
    uint16_t mAdvancedWidth;
    int32_t mCapHeight;
    std::shared_ptr<TextureResource> mpTexture;
};

#endif