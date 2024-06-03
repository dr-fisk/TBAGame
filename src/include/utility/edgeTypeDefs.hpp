#ifndef EDGE_TYPE_DEFS_HPP
#define EDGE_TYPE_DEFS_HPP\

template <typename T>
struct Edges
{
  T p1;
  T p2;
};

struct EdgeTableNode
{
  float yUpper;
  float yLower;
  float xIntersect;
  float dxPerScan;
};

#endif