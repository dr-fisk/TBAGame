#ifndef MESH_H
#define MESH_H

#include "drawable/drawable.h"
#include "drawable/rectangle.h"

class Mesh : public Drawable {
  public:
    Mesh();
    Mesh(const std::string &crPngFile, const uint8_t cLeft = 0, uint8_t cTop = 0, uint8_t cSize = 1);
    virtual ~Mesh();
    virtual std::vector<RenderData> getRenderData();
  private:
    std::vector<RenderData> mMesh;
};

#endif