#ifndef EDGE_TABLE_H

#include "Vector.h"
#include "common.h"
#include "plot_utility.h"

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
  bool edgeTableYLessThan(const EdgeTableNode &crNode1, const EdgeTableNode &crNode2);
  float currentXVal(const EdgeTableNode &crNode, const float cDy = 1.0);
  bool edgeTableXLessThan(const EdgeTableNode &crNode1, const EdgeTableNode &crNode2);
  void fillActiveEdgeTable(const std::vector<EdgeTableNode> &crEdgeTable, std::vector<EdgeTableNode> &rActiveEdgeTable,
                           uint32_t &rEdgeTableIdx, const uint32_t cNumEdges,
                           size_t &rActiveTableIdx, const int32_t cY);
  void sortEdgeTable(std::vector<EdgeTableNode> &rEdgeTable, const uint32_t cNumEdges);
  void sortActiveEdgeTable(std::vector<EdgeTableNode> &rActiveEdgeTable, const size_t cActiveTableIdx);
  void updateActiveTableXVals(std::vector<EdgeTableNode> &rActiveEdgeTable, const size_t cActiveTableIdx, const float cDy = 1.0);
  
  template<typename T>
  static void fillEdgeTable(const std::vector<Edges<T>> &crEdges, std::vector<EdgeTableNode> &rEdgeTable,
                            uint32_t &rNumEdges)
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
      p1.mX = crEdges[i].p1.mX;
      p1.mY = crEdges[i].p1.mY;
      p2.mX = crEdges[i].p2.mX;
      p2.mY = crEdges[i].p2.mY;
      biggerYVal = std::max(p1.mY, p2.mY);
      smallerYVal = std::min(p1.mY, p2.mY);

      if ((int)p1.mY == (int)p2.mY)
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
                           std::vector<uint32_t> &rBitmap, const lg::Color &crColor, const int32_t cMinY, char cha)
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

    std::ofstream fd;
    
    if (cha == '0')
     fd.open("AET.txt");

    for(int32_t y = cMinY; y < crDimensions.mY; y ++)
    {
        fillActiveEdgeTable(edgeTable, activeEdgeTable, edgeTableIdx, numEdges, activeEdgeTableIdx, y);
      if (cha == '0')
      {
        fd << y << std::endl;
        for(int i = 0; i < activeEdgeTableIdx; i ++)
        {
          fd << i << ": " << activeEdgeTable[i].yLower << ", " << activeEdgeTable[i].yUpper << ", " << activeEdgeTable[i].xIntersect << std::endl;
        }
      }

      for(int32_t dx = 0; dx < scanlineSubDiv; dx++)
      {
      //   scanline = dx * stepPerScanline;
        for(int32_t i = 0; i < activeEdgeTableIdx && activeEdgeTableIdx > 1; i += 2)
        {
          startIntersection = activeEdgeTable[i].xIntersect;
          startIndex = activeEdgeTable[i].xIntersect;
          startCovered = (startIndex + 1) - startIntersection;

          endIntersection = activeEdgeTable[i + 1].xIntersect;
          endIndex = activeEdgeTable[i + 1].xIntersect;
          endCovered = endIntersection - (endIndex);

          // if (startIndex < 0 || startIndex >= crDimensions.mX || endIndex < 0 || endIndex >= crDimensions.mX )
          // {
          //   continue;
          // }
          if (cha == '0' && y == 157)
          {
            std::cout << "Start: " << startIndex << " End: " << endIndex << std::endl;
          }

          if(startIndex == endIndex)
          {
            idx1 = (y * crDimensions.mX) + startIndex;
            alpha = lg::Color(rBitmap[idx1]).getAlpha();
            tempColor = lg::Color(crColor.getRed(), crColor.getGreen(), crColor.getBlue(),
                                  alphaWeight * startCovered);
            tempColor.addAlpha(alpha);
            rBitmap[idx1] = crColor.getRgba();
          }
          else
          {
            idx1 = (y * crDimensions.mX) + startIndex;
            idx2 = (y * crDimensions.mX) + endIndex;
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
            if (endIndex < startIndex && cha == '0')
            std::cout << "Why less\n";
          }

          for (int32_t x = startIndex + 1; x < endIndex; x ++)
          {	
            pt = {x, y};
            alpha = lg::Color(rBitmap[crDimensions.mX * y + x]).getAlpha();
            tempColor = lg::Color(crColor.getRed(), crColor.getGreen(), crColor.getBlue(), alphaWeight);
            tempColor.addAlpha(alpha);
            PlotUtility<int32_t>::drawPixelInBitmap(pt, rBitmap, crDimensions.mX, tempColor);
          }
        }

        if (y == crDimensions.mY)
          break;

        updateActiveTableXVals(activeEdgeTable, activeEdgeTableIdx, stepPerScanline);
        sortActiveEdgeTable(activeEdgeTable, activeEdgeTableIdx);
      }

      // for(int i = 0; i < activeEdgeTableIdx; i ++)
      // {
      //   if ( i + 1 < activeEdgeTableIdx && activeEdgeTable[i].xIntersect == activeEdgeTable[i + 1].xIntersect &&
      //          (activeEdgeTable[i].yUpper != activeEdgeTable[i + 1].yUpper || activeEdgeTable[i].yLower != activeEdgeTable[i + 1].yLower))
      //          {
      //           std::cout << "Matched.\n";
      //          }
      //   if (activeEdgeTable[i].yUpper == y)
      //   {
      //     for(int j = i; j < activeEdgeTableIdx - 1; j ++)
      //     {
      //       activeEdgeTable[j] = activeEdgeTable[j + 1];
      //     }
      //     activeEdgeTableIdx --;
      //     i--;
      //   }
      // }

      // break;
    }
  }
};

#endif