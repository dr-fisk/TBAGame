#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "utility/net_utility.h"
#include "resource/font.h"
#include "drawable.h"
#include "renderEngine/renderEngine.h"
#include "shapes/box.h"

class Text : public Drawable
{
  public:
    Text() = default;
    Text(std::shared_ptr<Font>& prFont, const std::string& crText, std::shared_ptr<RenderEngine>& prRenderEngine,
         const uint8_t cCharSize, const Vector2<float>& crPos,
         const int32_t cLineWrap=-1, const float cLineHeight=1.2f);
    void gridfitText(const Vector2<float>& crTopLeft);
    void updateText(const std::string& crText);
    std::shared_ptr<TextureResource> getResource();
    bool hasResource();
    bool textureBounded();
    void movePos(const Vector2<float>& crMoveVector);
    void setPos(const Vector2<float>& crPos);
    Vector2<float> getPos();
    std::string getText();
    Vector2<float> getSize();
    void draw();
    ~Text();
  private:
    std::shared_ptr<Font> mpFont;
    std::string mText;
    std::vector<Vertex> mVertexes;
    Box<float> mBox;
    int32_t mLineWrap;
    int32_t mLineSpace;
    uint8_t mCharSize;
    uint16_t mAdvancedWidth;
    int32_t mCapHeight;
    std::shared_ptr<TextureResource> mTexture;
};

#endif