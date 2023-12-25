#ifndef VERTEX_UTILITY_H
#define VERTEX_UTILITY_H

#include "glcommon.h"
#include "Vector.h"

namespace VertexUtility
{
  void setVertexTextureIndex(Vertex& rVertex, const float cTextureIndex=-1.0f);

  template <typename T>
  Vertex createVertex(const Vector2<T>& crPos, const Vector2<T>& crSize, const lg::Color& crColor)
  {
    GLfloat wWidth = gWindowWidth / 2.0f;
    GLfloat wHeight = gWindowHeight / 2.0f;

    GLfloat x1 = (static_cast<GLfloat>(crPos.x) / wWidth) - 1.0f;
    GLfloat x2 = ((static_cast<GLfloat>(crPos.x) + static_cast<GLfloat>(crSize.x)) / wWidth) - 1.0f;
    GLfloat y1 = -1 * ((static_cast<GLfloat>(crPos.y) / wHeight) - 1.0f);
    GLfloat y2 = -1 * (((static_cast<GLfloat>(crPos.y) + static_cast<GLfloat>(crSize.y)) / wHeight) - 1.0f);

    // These need to be updated to reflect actual size / maxSize of texture
    const Vector2<GLfloat> textCoord1(0.0f, 1.0f);
    const Vector2<GLfloat> textCoord2(1.0f, 1.0f);
    const Vector2<GLfloat> textCoord3(1.0f, 0.0f);
    const Vector2<GLfloat> textCoord4(0.0f, 0.0f);

  return {  Vector2<GLfloat>(x1, y2), crColor, textCoord1, -1.0f,
            Vector2<GLfloat>(x2, y2), crColor, textCoord2, -1.0f,
            Vector2<GLfloat>(x2, y1), crColor, textCoord3, -1.0f,
            Vector2<GLfloat>(x1, y1), crColor, textCoord4, -1.0f };
  }

  template <typename T>
  void updateTextureCoordinates(Vertex& rVertex, const Vector2<T>& crActualSize, const Vector2<T>& crTextureSize)
  {
    const float xCoord = static_cast<float>(crActualSize.x) / static_cast<float>(crTextureSize.x);
    const float yCoord = static_cast<float>(crActualSize.y) / static_cast<float>(crTextureSize.y);

    rVertex.textCoord1 = Vector2<GLfloat>(0.0f, yCoord);
    rVertex.textCoord2 = Vector2<GLfloat>(xCoord, yCoord);
    rVertex.textCoord3 = Vector2<GLfloat>(xCoord,0.0f);
    rVertex.textCoord4 = Vector2<GLfloat>(0.0f, 0.0f);
  }
};

#endif