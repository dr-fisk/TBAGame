#include "utility/vertexUtility.h"

namespace VertexUtility
{
  //! @brief Sets Texture Index for Vertex
  //!
  //! @param[out] rData        Vertex to update Texture Index for
  //! @param[in] cTextureIndex Texture Index to store in Vertex
  //!
  //! @return None
  void setVertexTextureIndex(Vertex& rData, const float cTextureIndex)
  {
    rData.textureIndex1 = cTextureIndex;
    rData.textureIndex2 = cTextureIndex;
    rData.textureIndex3 = cTextureIndex;
    rData.textureIndex4 = cTextureIndex;
  }
};
