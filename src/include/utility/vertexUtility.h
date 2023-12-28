#ifndef VERTEX_UTILITY_H
#define VERTEX_UTILITY_H

#include "glcommon.h"
#include "Vector.h"

namespace VertexUtility
{
  void setVertexTextureIndex(Vertex& rVertex, const float cTextureIndex=-1.0f);

  //! @brief Creates Vertex Data for rendering
  //!
  //! @param[in] crPos   Position of Quad
  //! @param[in] crSize  Size of Quad
  //! @param[in] crColor Color of Quad can be transparent if Texture will be rendered onto Quad
  //!
  //! @return Vertex Data
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

  //! @brief Updates Texture Coordinates in Vertex Data
  //!
  //! @param[out] rVertex       Vertex to update Texture Coordinates for
  //! @param[in]  crActualSize  Size of Quad
  //! @param[in]  crTextureSize Size of Texture
  //!
  //! @return None
  template <typename A, typename B, typename C>
  void updateTextureCoordinates(Vertex& rVertex, const Vector2<A>& crActualSize, const Vector2<B>& crOffset,
                                const Vector2<C>& crTextureSize)
  {
    const float xMax = static_cast<float>(crActualSize.x + crOffset.x) / static_cast<float>(crTextureSize.x);
    const float yMax = static_cast<float>(crActualSize.y + crOffset.y) / static_cast<float>(crTextureSize.y);
    const float xMin = static_cast<float>(crOffset.x) / static_cast<float>(crTextureSize.x);
    const float yMin = static_cast<float>(crOffset.y) / static_cast<float>(crTextureSize.y);

    rVertex.textCoord1 = Vector2<GLfloat>(xMin, yMax);
    rVertex.textCoord2 = Vector2<GLfloat>(xMax, yMax);
    rVertex.textCoord3 = Vector2<GLfloat>(xMax, yMin);
    rVertex.textCoord4 = Vector2<GLfloat>(xMin, yMin);
  }
};

#endif