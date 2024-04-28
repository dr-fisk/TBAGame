#include "drawable/dot.hpp"

Dot::Dot()
{
  mRenderId = 0;
  mRender = false;
  mGeometryNeedUpdate = false;
  mRender = true;
}

void Dot::setRenderId(const uint64_t cRenderId)
{
  mRenderId = cRenderId;
}

uint64_t Dot::getRenderId()
{
  return mRenderId;
}

void Dot::setRender(const bool cEnable)
{
  mRender = cEnable;
}

bool Dot::getRender()
{
  return mRender;
}