#include "utility/vertexUtility.h"

namespace VertexUtility
{
  //! @brief Sets Texture Index for Vertex
  //!
  //! @param[out] rData         Vertex to update Texture Index for
  //! @param[in]  cTextureIndex Texture Index to store in Vertex
  //!
  //! @return None
  void setVertexTextureIndex(Vertex& rData, const float cTextureIndex)
  {
    rData.TextureIndex = cTextureIndex;
    // rData.textureIndex2 = cTextureIndex;
    // rData.textureIndex3 = cTextureIndex;
    // rData.textureIndex4 = cTextureIndex;
  }

  //! @brief Sets the color for Vertex
  //!
  //! @param[out] rVertex Vertex to have color set
  //! @param[in] crColor  Color to set in Vertex
  //!
  //! @return None
  void setVertexColor(Vertex& rVertex, const lg::Color& crColor)
  {
  rVertex.Rgba = crColor;
  // rVertex.rgba2 = crColor;
  // rVertex.rgba3 = crColor;
  // rVertex.rgba4 = crColor;
  }
};
