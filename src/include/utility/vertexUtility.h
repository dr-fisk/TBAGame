#ifndef VERTEX_UTILITY_H
#define VERTEX_UTILITY_H

#include <iostream>

#include "glcommon.h"
#include "glm/vec2.hpp"

namespace VertexUtility
{
  void setVertexTextureIndex(Vertex& rVertex, const float cTextureIndex=-1.0f);

  //! @brief Creates Vertex Data for rendering
  //!
  //! @param[in] crPos       Position of Quad
  //! @param[in] crSize      Size of Quad
  //! @param[in] crColor     Color of Quad can be transparent if Texture will be rendered onto Quad
  //! @param[in] cTextureIdx Texture Coordinate to set in Vertex
  //!
  //! @return Vertex Data
  template <typename A, typename B>
  Vertex createVertex(const A& crPos, const B& crSize, const lg::Color& crColor,
                      const float cTextureIdx=-1.0f)
  {
    GLfloat wWidth = gWindowWidth / 2.0f;
    GLfloat wHeight = gWindowHeight / 2.0f;

    GLfloat x1 = (static_cast<GLfloat>(crPos.x) / wWidth) - 1.0f;
    GLfloat x2 = ((static_cast<GLfloat>(crPos.x) + static_cast<GLfloat>(crSize.x)) / wWidth) - 1.0f;
    GLfloat y1 = -1 * ((static_cast<GLfloat>(crPos.y) / wHeight) - 1.0f);
    GLfloat y2 = -1 * (((static_cast<GLfloat>(crPos.y) + static_cast<GLfloat>(crSize.y)) / wHeight) - 1.0f);

    // These need to be updated to reflect actual size / maxSize of texture
    const glm::vec2 textCoord1(0.0f, 1.0f);
    const glm::vec2 textCoord2(1.0f, 1.0f);
    const glm::vec2 textCoord3(1.0f, 0.0f);
    const glm::vec2 textCoord4(0.0f, 0.0f);

  return {  glm::vec2(x1, y2), crColor, textCoord1, cTextureIdx,
            glm::vec2(x2, y2), crColor, textCoord2, cTextureIdx,
            glm::vec2(x2, y1), crColor, textCoord3, cTextureIdx,
            glm::vec2(x1, y1), crColor, textCoord4, cTextureIdx };
  }

  //! @brief Creates Vertex Data for rendering
  //!
  //! @param[out] rVertex     Vertex to create in place
  //! @param[in]  crPos       Position of Quad
  //! @param[in]  crSize      Size of Quad
  //! @param[in]  crColor     Color of Quad can be transparent if Texture will be rendered onto Quad
  //! @param[in]  cTextureIdx Texture Coordinate to set in Vertex
  //!
  //! @return None
  template <typename A, typename B>
  void createVertex(Vertex& rVertex, const A& crPos, const B& crSize, const lg::Color& crColor,
                    const float cTextureIdx=-1.0f)
  {
    GLfloat wWidth = gWindowWidth / 2.0f;
    GLfloat wHeight = gWindowHeight / 2.0f;

    GLfloat x1 = (static_cast<GLfloat>(crPos.x) / wWidth) - 1.0f;
    GLfloat x2 = ((static_cast<GLfloat>(crPos.x) + static_cast<GLfloat>(crSize.x)) / wWidth) - 1.0f;
    GLfloat y1 = -1 * ((static_cast<GLfloat>(crPos.y) / wHeight) - 1.0f);
    GLfloat y2 = -1 * (((static_cast<GLfloat>(crPos.y) + static_cast<GLfloat>(crSize.y)) / wHeight) - 1.0f);

    // These need to be updated to reflect actual size / maxSize of texture
    const glm::vec2 textCoord4(0.0f, 1.0f);
    const glm::vec2 textCoord3(1.0f, 1.0f);
    const glm::vec2 textCoord2(1.0f, 0.0f);
    const glm::vec2 textCoord1(0.0f, 0.0f);

    
    rVertex.bottomLeft = glm::vec2(x1, y2);
    rVertex.rgba1 = crColor;
    rVertex.textCoord1 = textCoord1;
    rVertex.textureIndex1 = cTextureIdx;
    rVertex.bottomRight = glm::vec2(x2, y2);
    rVertex.rgba2 = crColor;
    rVertex.textCoord2 = textCoord2;
    rVertex.textureIndex2 = cTextureIdx;
    rVertex.topRight = glm::vec2(x2, y1);
    rVertex.rgba3 = crColor;
    rVertex.textCoord3 = textCoord3;
    rVertex.textureIndex3 = cTextureIdx;
    rVertex.topLeft = glm::vec2(x1, y1);
    rVertex.rgba4 = crColor;
    rVertex.textCoord4 = textCoord4;
    rVertex.textureIndex4 = cTextureIdx;
  }

  //! @brief Updates Vertex
  //!
  //! @param[out] rVertex     Vertex to create in place
  //! @param[in]  crPos       Position of Quad
  //! @param[in]  crSize      Size of Quad
  //! @param[in]  crColor     Color of Quad can be transparent if Texture will be rendered onto Quad
  //!
  //! @return None
  template<typename A, typename B>
  void updateVertex(Vertex& rVertex, const A& crPos, const B& crSize,
                    const lg::Color& crColor=lg::Transparent)
  {
    GLfloat wWidth = gWindowWidth / 2.0f;
    GLfloat wHeight = gWindowHeight / 2.0f;

    GLfloat x1 = (static_cast<GLfloat>(crPos.x) / wWidth) - 1.0f;
    GLfloat x2 = ((static_cast<GLfloat>(crPos.x) + static_cast<GLfloat>(crSize.x)) / wWidth) - 1.0f;
    GLfloat y1 = -1 * ((static_cast<GLfloat>(crPos.y) / wHeight) - 1.0f);
    GLfloat y2 = -1 * (((static_cast<GLfloat>(crPos.y) + static_cast<GLfloat>(crSize.y)) / wHeight) - 1.0f);

    rVertex.bottomLeft = glm::vec2(x1, y2);
    rVertex.bottomRight = glm::vec2(x2, y2);
    rVertex.topRight = glm::vec2(x2, y1);
    rVertex.topLeft = glm::vec2(x1, y1);
    rVertex.rgba1 = crColor;
    rVertex.rgba2 = crColor;
    rVertex.rgba3 = crColor;
    rVertex.rgba4 = crColor;
  }

  //! @brief Updates Texture Coordinates in Vertex Data
  //!
  //! @param[out] rVertex       Vertex to update Texture Coordinates for
  //! @param[in]  crActualSize  Size of Quad
  //! @param[in]  crTextureSize Size of Texture
  //! @param[in]  cInvert       Inverts texture coordinates
  //!
  //! @return None
  template <typename A, typename B, typename C>
  void updateTextureCoordinates(Vertex& rVertex, const A& crActualSize, const B& crOffset,
                                const C& crTextureSize, const bool cInvert=false)
  {
    const float xMax = static_cast<float>(crActualSize.x + crOffset.x) / static_cast<float>(crTextureSize.x);
    const float yMax = static_cast<float>(crActualSize.y + crOffset.y) / static_cast<float>(crTextureSize.y);
    const float xMin = static_cast<float>(crOffset.x) / static_cast<float>(crTextureSize.x);
    const float yMin = static_cast<float>(crOffset.y) / static_cast<float>(crTextureSize.y);

    if(!cInvert)
    {
      rVertex.textCoord1 = glm::vec2(xMin, yMax);
      rVertex.textCoord2 = glm::vec2(xMax, yMax);
      rVertex.textCoord3 = glm::vec2(xMax, yMin);
      rVertex.textCoord4 = glm::vec2(xMin, yMin);
    }
    else
    {
      rVertex.textCoord4 = glm::vec2(xMin, yMax);
      rVertex.textCoord3 = glm::vec2(xMax, yMax);
      rVertex.textCoord2 = glm::vec2(xMax, yMin);
      rVertex.textCoord1 = glm::vec2(xMin, yMin);
    }
  }

  void setVertexColor(Vertex& rVertex, const lg::Color& crColor);
};

#endif