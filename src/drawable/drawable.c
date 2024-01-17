#include "drawable/drawable.h"
#include "renderEngine/renderKey.h"

void Drawable::setRenderId(const uint64_t cRenderId)
{
  mRenderId = cRenderId;
}

uint64_t Drawable::getRenderId()
{
  return mRenderId;
}

void Drawable::setRender(const bool cEnable)
{
  mRender = cEnable;
}

bool Drawable::getRender()
{
  return mRender;
}