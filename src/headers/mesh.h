#ifndef MESH_H
#define MESH_H

#include "Drawable.h"
#include "rectangle.h"

class Mesh : public Drawable {
  public:
    Mesh();
    Mesh(std::string pngFile, uint8_t left = 0, uint8_t top = 0, uint8_t size = 1);
    virtual ~Mesh();
    virtual std::vector<RenderData> getRenderData();
  private:
    std::vector<RenderData> mesh;
};

#endif