#include "edgeTable.h"

#include <algorithm>

namespace EdgeTable
{
  bool edgeTableYLessThan(const EdgeTableNode &crNode1, const EdgeTableNode &crNode2)
  {
    return (crNode1.yLower < crNode2.yLower);
  }

  float currentXVal(const EdgeTableNode &crNode, const float cDy)
  {
    return crNode.xIntersect + cDy * crNode.dxPerScan;
  }

  bool edgeTableXLessThan(const EdgeTableNode &crNode1, const EdgeTableNode &crNode2)
  {
    return crNode1.xIntersect < crNode2.xIntersect;
  }

  void fillActiveEdgeTable(const std::vector<EdgeTableNode> &crEdgeTable, std::vector<EdgeTableNode> &rActiveEdgeTable,
                           uint32_t &rEdgeTableIdx, const uint32_t cNumEdges, size_t &rActiveTableIdx,
                           const int32_t cY)
  {
    for(int i = rEdgeTableIdx; i < cNumEdges; i ++)
    {
      if (crEdgeTable[i].yLower == cY)
      {
        rEdgeTableIdx ++;
        rActiveEdgeTable[rActiveTableIdx] = crEdgeTable[i];
        rActiveTableIdx ++;
      }
    }

    sortActiveEdgeTable(rActiveEdgeTable, rActiveTableIdx);

    for(int i = 0; i < rActiveTableIdx; i ++)
    {
      if (rActiveEdgeTable[i].yUpper == cY)
      {
        for(int j = i; j < rActiveTableIdx - 1; j ++)
        {
          rActiveEdgeTable[j] = rActiveEdgeTable[j + 1];
        }
        rActiveTableIdx --;
        i--;
      }
    }
  }

  void sortEdgeTable(std::vector<EdgeTableNode> &rEdgeTable, const uint32_t cNumEdges)
  {
    std::sort(rEdgeTable.begin(), rEdgeTable.begin() + cNumEdges, EdgeTable::edgeTableYLessThan);
  }

  void sortActiveEdgeTable(std::vector<EdgeTableNode> &rActiveEdgeTable, const size_t cActiveTableIdx)
  {
    std::sort(rActiveEdgeTable.begin(), rActiveEdgeTable.begin() + cActiveTableIdx, EdgeTable::edgeTableXLessThan);
  }

  void updateActiveTableXVals(std::vector<EdgeTableNode> &rActiveEdgeTable, const size_t cActiveTableIdx, const float cDy)
  {
    for(int i = 0; i < cActiveTableIdx; i ++)
    {
      rActiveEdgeTable[i].xIntersect = currentXVal(rActiveEdgeTable[i], cDy);
    }
  }
};