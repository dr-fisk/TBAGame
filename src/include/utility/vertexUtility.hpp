#ifndef VERTEX_UTILITY_HPP
#define VERTEX_UTILITY_HPP

#include "vertex.hpp"
#include "shapes/rect.hpp"

namespace lre
{
void generateTextureCoords(const glm::vec2& crTextureOffset, const glm::vec2& crSubTextureSize,
  const glm::vec2& crTextureSize, std::array<Vertex, sNumQuadVerts>& rVertexes, const bool cInvert=false);

bool clipVertexToBounds(const Rect<float>& crQuad, const Rect<float>& crBounds,
  const glm::vec2& crSubTextureSize, const glm::vec2& crTextureSize,
  std::array<Vertex, sNumQuadVerts>& rVertexes);
}

#endif