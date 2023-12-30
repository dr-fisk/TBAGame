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
    ~Sprite() = default;
    std::shared_ptr<TextureResource> getResource();
    bool needUpdate();
    void getVertex(std::vector<Vertex>& rBatchVertexes, uint32_t& rVertexIdx);
    bool hasResource();
    bool textureBounded();
    void movePos(float cX, float cY);
  private:
    lg::Color mColor;
    Vector2<float> mPos;
    Vector2<float> mDimensions;
    std::shared_ptr<TextureResource> mTexture;
    Vertex mVertex;
};

#endif