#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "utility/net_utility.h"
#include "resource/font.h"
#include "drawable.h"
#include "renderEngine/renderEngine.h"
#include "renderEngine/batchBuffer.h"

class Text : public Drawable
{
  public:
    Text() = default;
    Text(std::shared_ptr<Font>& prFont, const std::string& crText, std::shared_ptr<RenderEngine>& prRenderEngine,
         std::shared_ptr<BatchBuffer>& prBatch, const uint8_t cCharSize, const float cTop, const float cLeft,
         const int32_t cLineWrap=-1, const float cLineHeight=1.2f);
    void gridfitText();
    void updateText(const std::string& crText);
    std::shared_ptr<TextureResource> getResource();
    void getVertex(std::vector<Vertex>& rBatchVertexes, uint32_t& rVertexIdx);
    bool hasResource();
    bool textureBounded();
    void movePos(const float cX, const float cY);
    void setPos(const float cLeft, const float cTop);
    Vector2<float> getPos();
    std::string getText();
    Vector2<uint32_t> getSize();
    ~Text();
  private:
    std::shared_ptr<Font> mpFont;
    std::string mText;
    std::vector<Vertex> mVertexes;

    Vector2<float> mPos;
    Vector2<uint32_t> mDimensions;
    int32_t mLineWrap;
    int32_t mLineSpace;
    uint8_t mCharSize;
    uint16_t mAdvancedWidth;
    int32_t mCapHeight;
    std::shared_ptr<TextureResource> mTexture;
};

#endif