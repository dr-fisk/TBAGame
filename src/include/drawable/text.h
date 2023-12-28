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
         std::shared_ptr<BatchBuffer>& prBatch, const uint8_t cCharSize, const int32_t cTop, const int32_t cLeft,
         const int32_t cLineWrap=-1);
    std::vector<Vertex> getVertex();
    std::vector<VertexData> getVertexData();
    void gridfitText();
    TextureResource& getResource();
    ~Text();
  private:
    std::shared_ptr<Font> mpFont;
    std::string mText;
    std::vector<Vertex> mVertexes;
    std::vector<VertexData> mVertexesData;

    int32_t mTop;
    int32_t mLeft;
    int32_t mLineWrap;
    uint8_t mCharSize;
};

#endif