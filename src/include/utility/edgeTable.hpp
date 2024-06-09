#ifndef EDGE_TABLE_HPP
#define EDGE_TABLE_HPP

#include <cstdint>
#include <vector>
#include <fstream>
#include <iostream>

#include "color.hpp"
#include "utility/edgeTypeDefs.hpp"
#include "common.hpp"
#include "glm/vec2.hpp"

namespace EdgeTable
{
  bool edgeTableYLessThan(const EdgeTableNode& crNode1, const EdgeTableNode& crNode2);
  float currentXVal(const EdgeTableNode& crNode, const float cDy = 1.0);
  bool edgeTableXLessThan(const EdgeTableNode &crNode1, const EdgeTableNode& crNode2);
  void fillActiveEdgeTable(const std::vector<EdgeTableNode>& crEdgeTable, std::vector<EdgeTableNode>& rActiveEdgeTable,
                           uint32_t& rEdgeTableIdx, const uint32_t cNumEdges,
                           size_t& rActiveTableIdx, const float cY);
  void sortEdgeTable(std::vector<EdgeTableNode>& rEdgeTable, const uint32_t cNumEdges);
  void sortActiveEdgeTable(std::vector<EdgeTableNode>& rActiveEdgeTable, const size_t cActiveTableIdx);
  void updateActiveTableXVals(std::vector<EdgeTableNode>& rActiveEdgeTable, const size_t cActiveTableIdx,
                              const float cDy = 1.0);
  bool skipCurrentEdge(const EdgeTableNode &crNode1, const EdgeTableNode& crNode2);

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
    T p1 = {0, 0};
    T p2 = {0, 0};
    for (int32_t i = 0; i < crEdges.size(); i ++)
    {
      p1.x = crEdges[i].p1.x;
      p1.y = crEdges[i].p1.y;
      p2.x = crEdges[i].p2.x;
      p2.y = crEdges[i].p2.y;
      biggerYVal = std::max(p1.y, p2.y);
      smallerYVal = std::min(p1.y, p2.y);

      if (decimalCmp(p1.y, p2.y))
      {
        continue;
      }

      if (decimalCmp(p1.x, p2.x))
      {
        rEdgeTable[rNumEdges].dxPerScan = 0;
      }
      else
      {
        dy = p2.y - p1.y;
        dx = p2.x - p1.x;
        if(decimalCmp(dy, 0.0f))
        {
          rEdgeTable[rNumEdges].dxPerScan = 0;
        }
        else
        {
          rEdgeTable[rNumEdges].dxPerScan = dx / dy;
        }
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
  static void scanLineFill(const std::vector<Edges<T>>& crEdges, const glm::uvec2& crDimensions,
                           std::vector<uint32_t>& rBitmap, const lg::Color &crColor, const int32_t cMinY, char cha)
  {
    std::vector<EdgeTableNode> edgeTable(crEdges.size());
    std::vector<EdgeTableNode> activeEdgeTable(crEdges.size());
    size_t activeEdgeTableIdx = 0;
    uint32_t numEdges = 0;
    uint32_t edgeTableIdx = 0;
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
    float dy = 0;
    int intersection = 0;
    int prevStartIndex = -1;
    float pixelCoverage = 0;

    fillEdgeTable(crEdges, edgeTable, numEdges);

    for(int32_t y = cMinY; y < crDimensions.y; y ++)
    {
      dy = y;
      for(int32_t dx = 0; dx < scanlineSubDiv; dx++)
      {
        fillActiveEdgeTable(edgeTable, activeEdgeTable, edgeTableIdx, numEdges, activeEdgeTableIdx, dy);
        intersection = 0;
        for(int32_t i = 0; i < activeEdgeTableIdx && activeEdgeTableIdx > 1;)
        {
          startIntersection = activeEdgeTable[i].xIntersect;
          startIndex = static_cast<int32_t>(activeEdgeTable[i].xIntersect);
          startCovered = (startIndex + 1) - startIntersection;

          endIntersection = activeEdgeTable[i + 1].xIntersect;
          endIndex = static_cast<int32_t>(activeEdgeTable[i + 1].xIntersect);
          endCovered = endIntersection - endIndex;

          if((i - 1 > 0) && skipCurrentEdge(activeEdgeTable[i], activeEdgeTable[i - 1]))
          {
            i++;
            continue;
          }

          if(startIndex == endIndex)
          {
            idx1 = (y * crDimensions.x) + startIndex;
            uint8_t currAlpha = lg::Color::getAlpha(rBitmap[idx1]);
            alpha = lg::Color::getAlpha(rBitmap[idx1]);
            alpha += static_cast<uint8_t>(alphaWeight * startCovered);
            lg::Color::setAlpha(rBitmap[idx1], alpha);
          }
          else
          {
            idx1 = (y * crDimensions.x) + startIndex;
            idx2 = (y * crDimensions.x) + endIndex;
            uint8_t currAlpha = lg::Color::getAlpha(rBitmap[idx1]);

            alpha = lg::Color::getAlpha(rBitmap[idx1]);
            alpha += static_cast<uint8_t>(alphaWeight * startCovered);
            lg::Color::setAlpha(rBitmap[idx1], alpha);
            currAlpha = lg::Color::getAlpha(rBitmap[idx2]);

            alpha = lg::Color::getAlpha(rBitmap[idx2]);
            alpha += static_cast<uint8_t>(alphaWeight * endCovered);
            lg::Color::setAlpha(rBitmap[idx2], alpha);
          }

          for (int32_t x = startIndex + 1; x < endIndex; x ++)
          {	
            uint8_t currAlpha = lg::Color::getAlpha(rBitmap[crDimensions.x * y + x]);
            alpha = lg::Color::getAlpha(rBitmap[crDimensions.x * y + x]);
            alpha += static_cast<uint8_t>(alphaWeight);
            lg::Color::setAlpha(rBitmap[crDimensions.x * y + x], alpha);
          }

          i +=2;
        }

        updateActiveTableXVals(activeEdgeTable, activeEdgeTableIdx, stepPerScanline);
        dy += stepPerScanline;
      }
    }
  }
};

#endif