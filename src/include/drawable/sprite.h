#ifndef SPRITE_H
#define SPRITE_H

#include "glcommon.h"
#include "drawable/drawable.h"
#include "resource/textureResource.h"

class Sprite : public Drawable
{
  public:
    Sprite() = default;
    Sprite(const std::string& crPath, std::shared_ptr<RenderEngine>& prRenderEngine,
           std::shared_ptr<BatchBuffer>& prBatch,const float cTop, const float cLeft, const float cHeight,
           const float cWidth);
    Sprite(std::shared_ptr<BatchBuffer>& prBatch, const float cTop, const float cLeft, 
           const float cHeight, const float cWidth, const lg::Color& crColor);
    ~Sprite();
    std::shared_ptr<TextureResource> getResource();
    void getVertex(std::vector<Vertex>& rBatchVertexes, uint32_t& rVertexIdx);
    bool hasResource();
    bool textureBounded();
    void movePos(const float cX, const float cY);
    void setPos(const float cLeft, const float cTop);
    void setSize(const uint32_t cWidth, const uint32_t cHeight);
    Vector2<float> getPos();
    void setColor(const lg::Color& crColor);
    Vector2<uint32_t> getSize();
  private:
    lg::Color mColor;
    Vector2<float> mPos;
    Vector2<uint32_t> mDimensions;
    std::shared_ptr<TextureResource> mTexture;
    Vertex mVertex;
};

#endif