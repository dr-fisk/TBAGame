#ifndef MESH_16_H
#define MESH_16_H

#include "rectangle.h"

#define MESH16_MAX_SIZE 256

class Mesh16{
  public:
    Mesh16();
    Mesh16(GLfloat wWidth, GLfloat wHeight, uint8_t left = 0, uint8_t top = 0, uint8_t size = 1);
    ~Mesh16();
    std::vector<RectVertexData>& getMesh16Data();
  private:
    std::vector<RectVertexData> mesh;
};

#endif