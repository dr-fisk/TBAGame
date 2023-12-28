#ifndef EDGE_TABLE_H

#include "Vector.h"
#include "common.h"
#include "utility/plot_utility.h"

#include <cstdint>
#include <vector>
#include <fstream>
struct EdgeTableNode
{
  int32_t yUpper;
  int32_t yLower;
  float xIntersect;
  float dxPerScan;
};

namespace EdgeTable
{
  bool edgeTableYLessThan(const EdgeTableNode& crNode1, const EdgeTableNode& crNode2);
  float currentXVal(const EdgeTableNode& crNode, const float cDy = 1.0);
  bool edgeTableXLessThan(const EdgeTableNode &crNode1, const EdgeTableNode& crNode2);
  void fillActiveEdgeTable(const std::vector<EdgeTableNode>& crEdgeTable, std::vector<EdgeTableNode>& rActiveEdgeTable,
                           uint32_t& rEdgeTableIdx, const uint32_t cNumEdges,
                           size_t& rActiveTableIdx, const int32_t cY);
  void sortEdgeTable(std::vector<EdgeTableNode>& rEdgeTable, const uint32_t cNumEdges);
  void sortActiveEdgeTable(std::vector<EdgeTableNode>& rActiveEdgeTable, const size_t cActiveTableIdx);
  void updateActiveTableXVals(std::vector<EdgeTableNode>& rActiveEdgeTable, const size_t cActiveTableIdx,
                              const float cDy = 1.0);
  
  //! @brief Fills rEdgeTable from crEdges list
  //!
  //! @param[in]  crEdges    List of Edges to construct an Edge Table from
  //! @param[out] rEdgeTable Edge Table list of crEdges size initialized
  //! @param[out] rNumEdges  Number of edges inserted into Edge Table
  //!
  //! @return None
  template<typename T>
  static void fillEdgeTable(const std::vector<Edges<T>>& crEdges, std::vector<EdgeTableNode>& rEdgeTable,
                            uint32_t& rNumEdges)
  {
    float biggerYVal = 0;
    float smallerYVal = 0;
    float dx = 0;
    float dy = 0;
    float m = 0;
    Vector2<T> p1 = {0, 0};
    Vector2<T> p2 = {0, 0};
    for (int32_t i = 0; i < crEdges.size(); i ++)
    {
      p1.x = crEdges[i].p1.x;
      p1.y = crEdges[i].p1.y;
      p2.x = crEdges[i].p2.x;
      p2.y = crEdges[i].p2.y;
      biggerYVal = std::max(p1.y, p2.y);
      smallerYVal = std::min(p1.y, p2.y);

      if (static_cast<int32_t>(p1.y) == static_cast<int32_t>(p2.y))
      {
        continue;
      }

      if (p1.x == p2.x)
      {
        m = 0;
        rEdgeTable[rNumEdges].dxPerScan = m;
      }
      else
      {
        dy = static_cast<int32_t>(p2.y) - static_cast<int32_t>(p1.y);
        dx = p2.x - p1.x;
        m = dy / dx;
        rEdgeTable[rNumEdges].dxPerScan = 1.0 / m;
      }

      rEdgeTable[rNumEdges].yUpper = biggerYVal;
      rEdgeTable[rNumEdges].yLower = smallerYVal;
      rEdgeTable[rNumEdges].xIntersect = (p2.y > p1.y) ? p1.x : p2.x;
      rNumEdges ++;
    }

    sortEdgeTable(rEdgeTable, rNumEdges);
  }

  //! @brief Performs the Scanline fill algorithm and stores result in rBitmap
  //!        SubPixel AA involved TODO: Remove cha param
  //!
  //! @param[in]  crEdges      Edge Table
  //! @param[in]  crDimensions Dimensions of bitmap
  //! @param[out] rBitmap      Bitmap to construct polygon in
  //! @param[in]  crColor      Color to fill Bitmap with
  //! @param[in]  cMinY        Minimum Y Value to start Scanline fill algorithm
  //!
  //! @return None
  template<typename T>
  static void scanLineFill(const std::vector<Edges<T>>& crEdges, const Vector2<uint32_t>& crDimensions,
                           std::vector<uint32_t>& rBitmap, const lg::Color &crColor, const int32_t cMinY, char cha)
  {
    std::vector<EdgeTableNode> edgeTable(crEdges.size());
    std::vector<EdgeTableNode> activeEdgeTable(crEdges.size());
    size_t activeEdgeTableIdx = 0;
    uint32_t numEdges = 0;
    uint32_t edgeTableIdx = 0;
    Vector2<int32_t> pt = {0,0};
    float scanlineSubDiv = 5;
    float alphaWeight = 255.0 / scanlineSubDiv;
    float stepPerScanline = 1.0 / scanlineSubDiv;
    float startIntersection = 0;
    int32_t startIndex = 0;
    float startCovered = 0;
    float endIntersection = 0;
    int32_t endIndex = 0;
    float endCovered = 0;
    float scanline = 0;
    int32_t idx1 = 0;
    int32_t idx2 = 0;
    lg::Color tempColor;
    uint8_t alpha = 0;

    fillEdgeTable(crEdges, edgeTable, numEdges);

    for(int32_t y = cMinY; y < crDimensions.y; y ++)
    {
        fillActiveEdgeTable(edgeTable, activeEdgeTable, edgeTableIdx, numEdges, activeEdgeTableIdx, y);

      for(int32_t dx = 0; dx < scanlineSubDiv; dx++)
      {
        for(int32_t i = 0; i < activeEdgeTableIdx && activeEdgeTableIdx > 1; i += 2)
        {
          startIntersection = activeEdgeTable[i].xIntersect;
          startIndex = activeEdgeTable[i].xIntersect;
          startCovered = (startIndex + 1) - startIntersection;

          endIntersection = activeEdgeTable[i + 1].xIntersect;
          endIndex = activeEdgeTable[i + 1].xIntersect;
          endCovered = endIntersection - (endIndex);

          if (startIndex < 0 || startIndex >= crDimensions.x || endIndex < 0 || endIndex >= crDimensions.x )
          {
            std::cout << "Hit the badspot\n";
          }

          if(startIndex == endIndex)
          {
            idx1 = (y * crDimensions.x) + startIndex;
            alpha = lg::Color(rBitmap[idx1]).getAlpha();
            tempColor = lg::Color(crColor.getRed(), crColor.getGreen(), crColor.getBlue(),
                                  alphaWeight * startCovered);
            tempColor.addAlpha(alpha);
            rBitmap[idx1] = crColor.getRgba();
          }
          else
          {
            idx1 = (y * crDimensions.x) + startIndex;
            idx2 = (y * crDimensions.x) + endIndex;
            alpha = lg::Color(rBitmap[idx1]).getAlpha();
            tempColor = lg::Color(crColor.getRed(), crColor.getGreen(), crColor.getBlue(),
                                  alphaWeight * startCovered);
            tempColor.addAlpha(alpha);
            rBitmap[idx1] = tempColor.getRgba();
            alpha = lg::Color(rBitmap[idx2]).getAlpha();
            tempColor = lg::Color(crColor.getRed(), crColor.getGreen(), crColor.getBlue(),
                                  alphaWeight * endCovered);
            tempColor.addAlpha(alpha);
            rBitmap[idx2] = tempColor.getRgba();
          }

          for (int32_t x = startIndex + 1; x < endIndex; x ++)
          {	
            pt = {x, y};
            alpha = lg::Color(rBitmap[crDimensions.x * y + x]).getAlpha();
            tempColor = lg::Color(crColor.getRed(), crColor.getGreen(), crColor.getBlue(), alphaWeight);
            tempColor.addAlpha(alpha);
            PlotUtility<int32_t>::drawPixelInBitmap(pt, rBitmap, crDimensions.x, tempColor);
          }
        }

        updateActiveTableXVals(activeEdgeTable, activeEdgeTableIdx, stepPerScanline);
      }
    }
  }
};

#endif