#include "mesh16.h"
#include "png.h"

Mesh16::Mesh16(GLfloat wWidth, GLfloat wHeight, uint8_t left, uint8_t top,uint8_t size) {
  Rect rect;
  uint32_t l = 0;
  uint32_t t = 0;
  std::vector<struct RGB> imgData;
  /* Temp until I update makefile */
  imgData = readPng("../src/heart.png");
  // If size = 0 then there will be rectangles with area 0 so skip
  for (int i = 0; i < MESH16_MAX_SIZE && size > 0; i ++) {
    t = ((i / 16) + top) * size;
    l = ((i % 16) + left) * size;

    rect = Rect(l, t, size, size);
    rect.setColor(imgData[i].Red, imgData[i].Green, imgData[i].Blue);

    mesh.push_back(rect.createRectVertexData(wWidth, wHeight));
  }
}

std::vector<RectVertexData>& Mesh16::getMesh16Data() {
  return mesh;
}

Mesh16::~Mesh16() {

}