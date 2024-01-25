#ifndef RENDERER2D_HPP
#define RENDERER2D_HPP

#include <memory>
#include <array>

#include "renderEngine/vertexArray.hpp"
#include "renderEngine/vertexBuffer.hpp"
#include "renderEngine/indexBuffer.hpp"
#include "renderEngine/shader.hpp"
#include "resource/textureResource.hpp"
#include "renderer/camera.hpp"

class Renderer2D
{
  public:
    static void init();
    static void beginScene(const std::shared_ptr<OrthCamera>& crpCamera);
    static void registerQuad(const glm::vec2& crPos, const glm::vec2& crSize,
                             std::array<Vertex, sNumQuadVerts>& rVertexes,
                             const std::shared_ptr<TextureResource>& crpTexture,
                             const bool cGeometryNeedUpdate);
    static void registerQuad(const glm::vec2& crPos, const glm::vec2& crSize,
                             std::array<Vertex, sNumQuadVerts>& rVertexes,
                             const lg::Color& crColor,
                             const bool cGeometryNeedUpdate);
    static void endScene();
    static void shutdown();
    static void flush();
    static void registerQuad(const glm::vec2& crPos, const glm::vec2& crPrevPos, const glm::vec2& crSize,
                              std::array<Vertex, sNumQuadVerts>& rVertexes,
                              const std::shared_ptr<TextureResource>& crpTexture,
                              const bool cGeometryNeedUpdate,
                              const double cDeltaTime);
  private:
    static void initBatch();
    static void nextBatch();
};

#endif