#include "mesh16.h"
#include "png.h"

Mesh16::Mesh16() {
}

Mesh16::Mesh16(GLfloat wWidth, GLfloat wHeight, std::string pngFile, uint8_t left, uint8_t top,uint8_t size) {
  Rect rect;
  uint32_t l = 0;
  uint32_t t = 0;
  uint32_t width = 0;
  uint32_t height = 0;
  std::vector<struct RGB> imgData;
  /* Temp until I update makefile */
  imgData = readPng(pngFile, width, height);
  // If size = 0 then there will be rectangles with area 0 so skip
  for (int i = 0; i < width * height && size > 0; i ++) {
    t = ((i / height) + top) * size;
    l = ((i % width) + left) * size;

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