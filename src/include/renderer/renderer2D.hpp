#ifndef RENDERER2D_HPP
#define RENDERER2D_HPP

#include <memory>
#include <array>

#include "renderer/camera.hpp"
#include "vertex.hpp"
#include "utility/transform.hpp"
#include "renderEngine/texture2D.hpp"
#include "shapes/rect.hpp"

class Renderer2D
{
  public:
    static void init();
    static void beginScene(const std::shared_ptr<OrthCamera>& crpCamera);
    static void registerQuad(const glm::vec2& crPos, const glm::vec2& crSize,
                             std::array<Vertex, sNumQuadVerts>& rVertexes,
                             const bool cGeometryNeedUpdate);
    static void registerQuad(const Transform& crTransform,
                             std::array<Vertex, sNumQuadVerts>& rVertexes,
                             const glm::vec2& cOffset);
    static void registerQuad(const Transform& crTransform,
                             std::array<Vertex, sNumQuadVerts>& rVertexes,
                             const Texture2D* cpTexture,
                             const glm::vec2& cOffset);
    static void registerQuad(const Transform& crTransform,
                             std::array<Vertex, sNumQuadVerts>& rVertexes,
                             const Texture2D* cpTexture,
                             const Rect<uint32_t>& crScissor,
                             const glm::vec2& cOffset);
    static void registerQuad(const glm::vec2& crPos, const glm::vec2& crSize,
                             std::array<Vertex, sNumQuadVerts>& rVertexes,
                             const Texture2D* cpTexture,
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