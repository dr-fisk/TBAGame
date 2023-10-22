#ifndef EDGE_TABLE_H

#include "Vector.h"
#include "plot_utility.h"

#include <cstdint>
#include <vector>

struct EdgeTableNode
{
  int32_t yUpper;
  int32_t yLower;
  float xIntersect;
  float dxPerScan;
};

namespace EdgeTable
{
  bool edgeTableYLessThan(const EdgeTableNode &crNode1, const EdgeTableNode &crNode2);
  float currentXVal(const EdgeTableNode &crNode);
  bool edgeTableXLessThan(const EdgeTableNode &crNode1, const EdgeTableNode &crNode2);
  void fillActiveEdgeTable(const std::vector<EdgeTableNode> &crEdgeTable, std::vector<EdgeTableNode> &rActiveEdgeTable,
                           uint32_t &rEdgeTableIdx, const uint32_t cNumEdges,
                           size_t &rActiveTableIdx, const int32_t cY);
  void sortEdgeTable(std::vector<EdgeTableNode> &rEdgeTable, const uint32_t cNumEdges);
  void sortActiveEdgeTable(std::vector<EdgeTableNode> &rActiveEdgeTable, const size_t cActiveTableIdx);
  void updateActiveTableXVals(std::vector<EdgeTableNode> &rActiveEdgeTable, const size_t cActiveTableIdx);
  
  template<typename T>
  static void fillEdgeTable(const std::vector<Edges<T>> &crEdges, std::vector<EdgeTableNode> &rEdgeTable,
                            uint32_t &rNumEdges)
  {
    int32_t biggerYVal = 0;
    int32_t smallerYVal = 0;
    float dx = 0;
    float dy = 0;
    float m = 0;
    Vector2<int32_t> p1 = {0, 0};
    Vector2<int32_t> p2 = {0, 0};
    for (int i = 0; i < crEdges.size(); i ++)
    {
      p1.mX = crEdges[i].p1.mX;
      p1.mY = crEdges[i].p1.mY;
      p2.mX = crEdges[i].p2.mX;
      p2.mY = crEdges[i].p2.mY;
      biggerYVal = std::max(p1.mY, p2.mY);
      smallerYVal = std::min(p1.mY, p2.mY);

      if (p1.mY == p2.mY)
      {
        continue;
      }

      if (p1.mX == p2.mX)
      {
        m = 0;
        rEdgeTable[rNumEdges].dxPerScan = m;
      }
      else
      {
        dy = p2.mY - p1.mY;
        dx = p2.mX - p1.mX;
        m = dy / dx;
        rEdgeTable[rNumEdges].dxPerScan = 1.0 / m;
      }

      rEdgeTable[rNumEdges].yUpper = biggerYVal;
      rEdgeTable[rNumEdges].yLower = smallerYVal;
      rEdgeTable[rNumEdges].xIntersect = (p2.mY > p1.mY) ? p1.mX : p2.mX;
      rNumEdges ++;
    }

    sortEdgeTable(rEdgeTable, rNumEdges);
  }

  template<typename T>
  static void scanLineFill(const std::vector<Edges<T>> &crEdges, const Vector2<int32_t> &crDimensions,
                           std::vector<uint32_t> &rBitmap, const lg::Color &crColor, const int32_t cMinY)
  {
    std::vector<EdgeTableNode> edgeTable(crEdges.size());
    std::vector<EdgeTableNode> activeEdgeTable(crEdges.size());
    size_t activeEdgeTableIdx = 0;
    uint32_t numEdges = 0;
    uint32_t edgeTableIdx = 0;
    Vector2<int32_t> pt = {0,0};

    fillEdgeTable(crEdges, edgeTable, numEdges);

    for(int32_t y = cMinY; y < crDimensions.mY; y ++)
    {
      if (y + 1 != crDimensions.mY)
      {
        fillActiveEdgeTable(edgeTable, activeEdgeTable, edgeTableIdx, numEdges, activeEdgeTableIdx, y);
      }

      for(int i = 0; i < activeEdgeTableIdx && activeEdgeTableIdx > 1; i += 2)
      {
        for (int x = activeEdgeTable[i].xIntersect; x <= activeEdgeTable[i + 1].xIntersect; x ++)
        {
          pt = {x, y};
          PlotUtility<int32_t>::drawPixelInBitmap(pt, rBitmap, crDimensions.mX, crColor);
        }
      }

      updateActiveTableXVals(activeEdgeTable, activeEdgeTableIdx);
    }
  }
};

#endif