#ifndef MESH_H
#define MESH_H

#include "rectangle.h"

#define MESH16_MAX_SIZE 256

class Mesh{
  public:
    Mesh();
    Mesh(GLfloat wWidth, GLfloat wHeight, std::string pngFile, uint8_t left = 0, uint8_t top = 0, uint8_t size = 1);
    ~Mesh();
    std::vector<RectVertexData>& getMeshData();
  private:
    std::vector<RectVertexData> mesh;
};

#endif