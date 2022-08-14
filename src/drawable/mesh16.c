#include "mesh16.h"

const std::string texture = "WWWWWBBBBBBWWWWWWWWBBRRRRRRBBWWWWWBRRRRRRRRRRBWWWBRRRRRRRRRRRRBWWBRRRRRRRRRRRRBWBRRRRRRRRRRRRRRBBRRRRRRRRRRRRRRBBRRRRRRRRRRRRRRBBBRRRRRBBBRRRRBBBWBBBBBBBBBBBBWBBBWWWWWBWBWWWWBBWBBBBBBBBBBBBBBWWBGGGGGBBBWWWWBWWWBGGGGGGGGGGBWWWWWBBGGGGGGBBWWWWWWWWBBBBBBWWWWW";

// Currently will only be at  a specific index, later add position to be configurable
Mesh16::Mesh16(GLfloat wWidth, GLfloat wHeight, uint8_t left, uint8_t top,uint8_t size) {
  Rect rect;
  uint32_t l = 0;
  uint32_t t = 0;

  // If size = 0 then there will be rectangles with area 0 so skip
  for (int i = 0; i < MESH16_MAX_SIZE && size > 0; i ++) {
    t = ((i / 16) + top) * size;
    l = ((i % 16) + left) * size;
    switch (texture[i]) {
      case 'W':
        rect = Rect(l, t, size, size);
        rect.setColor(lg::White);
        break;
      case 'B':
        rect = Rect(l, t, size, size);
        rect.setColor(lg::Black);
        break;
      case 'R':
        rect = Rect(l, t, size, size);
        rect.setColor(lg::Red);
        break;
      case 'G':
        rect = Rect(l, t, size, size);
        rect.setColor(lg::Grey);
        break;
      default:
        break;
    }

    mesh.push_back(rect.createRectVertexData(wWidth, wHeight));
  }

}

std::vector<RectVertexData>& Mesh16::getMesh16Data() {
  return mesh;
}

Mesh16::~Mesh16() {

}