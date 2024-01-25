#include "utility/edgeTable.hpp"

#include <algorithm>

namespace EdgeTable
{
  //! @brief Checks if crNode1's yLower value is smaller than crNode2's yLower value
  //!
  //! @param[in]  crNode1 Node1 from Edge Table
  //! @param[in]  crNode2 Node2 from Edge Table
  //!
  //! @return true if crNode1's yLower value is smaller than crNode2's yLower value
  //! @return false if crNode2's yLower value is smaller than crNode1's yLower value
  bool edgeTableYLessThan(const EdgeTableNode& crNode1, const EdgeTableNode& crNode2)
  {
    return (crNode1.yLower < crNode2.yLower);
  }

  //! @brief Updates the x intersection value of crNode from the following formula x + y * dx/dy
  //!
  //! @param[in]  crNode  Node from edge table to update x intersection
  //!
  //! @return New x intersection value
  float currentXVal(const EdgeTableNode& crNode, const float cDy)
  {
    return crNode.xIntersect + cDy * crNode.dxPerScan;
  }

  //! @brief Checks if crNode1's xIntersect value is smaller than crNode2's xIntersect value
  //!
  //! @param[in]  crNode1 Node1 from Edge Table
  //! @param[in]  crNode2 Node2 from Edge Table
  //!
  //! @return true if crNode1's xIntersect value is smaller than crNode2's xIntersect value
  //! @return false if crNode2's xIntersect value is smaller than crNode1's xIntersect value
  bool edgeTableXLessThan(const EdgeTableNode& crNode1, const EdgeTableNode& crNode2)
  {
    return crNode1.xIntersect < crNode2.xIntersect;
  }

  //! @brief Fills the Active Edge Table when an Edge in the Edge Table yLower value is equal to cY
  //!        The Active Edge Table is then sorted by least to greatest x intersections, and any Edge in Active Edge
  //!        Table whose yUpper is equal to cY is removed
  //!
  //! @param[in]   crEdgeTable      Edge Table to copy edges from
  //! @param[out]  rActiveEdgeTable Active Edge Table to copy new Edges into
  //! @param[out]  rEdgeTableIdx    Current index of crEdgeTable to avoid looping from the beginning of list
  //! @param[in]   cNumEdges        Number of Edges om EdgeTable
  //! @param[out]  rActiveTableIdx  Current Index in Active Edge Table to know where to place Edges into
  //! @param[in]   cY               Current Scanline
  //! @param[in]   cMaxY            Max Y value for current glyph
  //!
  //! @return None
  void fillActiveEdgeTable(const std::vector<EdgeTableNode>& crEdgeTable, std::vector<EdgeTableNode>& rActiveEdgeTable,
                           uint32_t& rEdgeTableIdx, const uint32_t cNumEdges, size_t& rActiveTableIdx,
                           const float cY, const uint32_t cMaxY)
  {
    for(int i = rEdgeTableIdx; i < cNumEdges; i ++)
    {
      if (crEdgeTable[i].yLower < cY || decimalCmp(cY, crEdgeTable[i].yLower))
      {
        rEdgeTableIdx ++;
        rActiveEdgeTable[rActiveTableIdx] = crEdgeTable[i];
        rActiveTableIdx ++;
      }
    }

    sortActiveEdgeTable(rActiveEdgeTable, rActiveTableIdx);

    for(int i = 0; i < rActiveTableIdx; i ++)
    {
      if (rActiveEdgeTable[i].yUpper < cY || decimalCmp(cY, rActiveEdgeTable[i].yUpper) || cY + 1 >= cMaxY)
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

  //! @brief Sort Edge Table via yLower values from least to greatest
  //!
  //! @param[out] crEdgeTable      Edge Table to sort
  //! @param[in]  cNumEdges        Number of Edges in Edge Table
  //!
  //! @return None
  void sortEdgeTable(std::vector<EdgeTableNode>& rEdgeTable, const uint32_t cNumEdges)
  {
    std::sort(rEdgeTable.begin(), rEdgeTable.begin() + cNumEdges, EdgeTable::edgeTableYLessThan);
  }

  //! @brief Sort Active Edge Table via xIntersect values from least to greatest
  //!
  //! @param[out] rActiveEdgeTable Active Edge Table to sort
  //! @param[in]  cActiveTableIdx  Number of Edges in Active Edge Table
  //!
  //! @return None
  void sortActiveEdgeTable(std::vector<EdgeTableNode>& rActiveEdgeTable, const size_t cActiveTableIdx)
  {
    std::sort(rActiveEdgeTable.begin(), rActiveEdgeTable.begin() + cActiveTableIdx, EdgeTable::edgeTableXLessThan);
  }

  //! @brief Updates the entire Active Edge Table list xIntersect Values
  //!
  //! @param[out] rActiveEdgeTable Active Edge Table to update xIntersect values
  //! @param[in]  cActiveTableIdx  Number of Edges in Active Edge Table
  //! @param[in]  cDy              Step amount to update xIntersect
  //!
  //! @return None
  void updateActiveTableXVals(std::vector<EdgeTableNode>& rActiveEdgeTable, const size_t cActiveTableIdx,
                              const float cDy)
  {
    for(int i = 0; i < cActiveTableIdx; i ++)
    {
      rActiveEdgeTable[i].xIntersect = currentXVal(rActiveEdgeTable[i], cDy);
    }
  }
};