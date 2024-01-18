#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "utility/net_utility.h"
#include "resource/font.h"
#include "drawable.h"
#include "renderEngine/renderEngine.h"
#include "shapes/box.h"
#include "glm/vec2.hpp"

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
    bool textureBounded();
    void movePos(const glm::vec2& crMoveVector);
    void setPos(const glm::vec2& crPos);
    glm::vec2 getPos();
    std::string getText();
    glm::vec2 getSize();
    void draw();
    ~Text();
  private:
    std::shared_ptr<Font> mpFont;
    std::string mText;
    std::vector<Vertex> mVertexes;
    Box<glm::vec2> mBox;
    int32_t mLineWrap;
    int32_t mLineSpace;
    uint8_t mCharSize;
    uint16_t mAdvancedWidth;
    int32_t mCapHeight;
    std::shared_ptr<TextureResource> mTexture;
};

#endif