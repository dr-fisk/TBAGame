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
#include "vertex.hpp"

class Renderer2D
{
  public:
    static void init();
    static void beginScene(const std::shared_ptr<OrthCamera>& crpCamera);
    static void registerQuad(const glm::vec2& crPos, const glm::vec2& crSize,
                             std::array<Vertex, sNumQuadVerts>& rVertexes,
                             const lg::Color& crColor,
                             const bool cGeometryNeedUpdate);
    static void registerQuad(const glm::vec2& crPos, const glm::vec2& crSize,
                             std::array<Vertex, sNumQuadVerts>& rVertexes,
                             const Texture2D* &crpTexture,
                             const bool cGeometryNeedUpdate);
    static void endScene();
    static void flush();
    static void nextBatch();
    static void registerContext(GLFWwindow* pOriginalContext, GLFWwindow* pNewContext);
    static void unregisterContext(GLFWwindow* pContext);
  private:
    static void initBatch();
};

#endif