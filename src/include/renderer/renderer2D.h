#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <memory>
#include <array>

#include "renderEngine/vertexArray.h"
#include "renderEngine/vertexBuffer.h"
#include "renderEngine/indexBuffer.h"
#include "renderEngine/shader.h"
#include "resource/textureResource.h"
#include "renderer/camera.h"

class Renderer2D
{
  public:
    static void init();
    static void beginScene(const OrthCamera& crCamera);
    static void registerQuad(const glm::vec2& crPos, const glm::vec2& crSize,
                             std::array<Vertex, sNumQuadVerts>& rVertexes,
                             const std::shared_ptr<TextureResource>& crpTexture);
    static void registerQuad(const glm::vec2& crPos, const glm::vec2& crSize,
                             std::array<Vertex, sNumQuadVerts>& rVertexes,
                             const lg::Color& crColor);
    static void endScene();
    static void shutdown();
    static void flush();
  private:
    static void initBatch();
    static void nextBatch();
};

#endif