#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include "utility/net_utility.h"
#include "drawable/drawable.h"
#include "glcommon.h"
#include "resource/textureResource.h"

class Mesh : public Drawable
{
  public:
    Mesh();
    Mesh(const std::string &crPngFile, const uint8_t cLeft = 0, uint8_t cTop = 0, uint8_t cSize = 1);
    virtual ~Mesh();
    virtual std::vector<Vertex> getVertex();
    std::shared_ptr<TextureResource> getResource() { return nullptr; }
    void getVertex(std::vector<Vertex>& rBatchVertexes, uint32_t& rVertexIdx){}
  private:
    std::vector<Vertex> mMesh;
};

#endif