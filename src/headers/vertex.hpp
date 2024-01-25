#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "color.hpp"
#include "glm/vec2.hpp"

struct Vertex
{
  glm::vec2 Pos;
  lg::Color Rgba;
  glm::vec2 TextCoord;
  float TextureIndex;
};

static const uint8_t sNumQuadVerts = 4;

#endif