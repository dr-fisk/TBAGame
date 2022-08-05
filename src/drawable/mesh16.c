#include "mesh16.h"

const std::string texture = "WWWWWBBBBBBWWWWWWWWBBRRRRRRBBWWWWWBRRRRRRRRRRBWWWWBRRRRRRRRRRBWWWBRRRRRRRRRRRRBWWBRRRRRRRRRRRRBWBRRRRRRRRRRRRRRBBRRRRRRRRRRRRRRBBRRRRRRRRRRRRRRBBBRRRRRBBBRRRRBBBWBBBBBBBBBBBBWBBBWWWWWBWBWWWWBBWBBBBBBBBBBBBBBWWBGGGGGBBBWWWWBWWWBGGGGGGGGGGBWWWWWBBGGGGGGBBWWWWWWWWBBBBBBWWWWW";


// Currently will only be at  a specific index, later add position to be configurable
Mesh16::Mesh16(GLfloat wWidth, GLfloat wHeight) {
  Rect rect;
  uint32_t left = 0;
  uint32_t top = 0;
  for (int i = 0; i < MESH16_MAX_SIZE; i ++) {
    top = i / 16 ;
    left = i % 16;
    switch (texture[i]) {
      case 'W':
        rect = Rect(left, top, PIXEL_SIZE, PIXEL_SIZE);
        rect.setColor(lg::White);
        break;
      case 'B':
        rect = Rect(left, top, PIXEL_SIZE, PIXEL_SIZE);
        rect.setColor(lg::Black);
        break;
      case 'R':
        rect = Rect(left, top, PIXEL_SIZE, PIXEL_SIZE);
        rect.setColor(lg::Red);
        break;
      case 'G':
        rect = Rect(left, top, PIXEL_SIZE, PIXEL_SIZE);
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