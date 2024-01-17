#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <memory>

#include "renderEngine/vertexArray.h"
#include "renderEngine/vertexBuffer.h"
#include "renderEngine/indexBuffer.h"
#include "renderEngine/shader.h"
#include "resource/textureResource.h"
#include "drawable/drawable.h"

class Renderer2D
{
  public:
    static void init();
    static void beginScene();
    static void registerQuad(const Vertex& crVertex, const std::shared_ptr<TextureResource>& crpTexture);
    static void endScene();
    static void shutdown();
    static void flush();
  private:
    static void initBatch();
    static void nextBatch();
};

#endif