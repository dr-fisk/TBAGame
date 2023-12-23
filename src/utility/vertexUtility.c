#include "utility/vertexUtility.h"

namespace VertexUtility
{
  void setVertexTextureIndex(Vertex &rData, const float cTextureIndex)
  {
    rData.textureIndex1 = cTextureIndex;
    rData.textureIndex2 = cTextureIndex;
    rData.textureIndex3 = cTextureIndex;
    rData.textureIndex4 = cTextureIndex;
  }
};
