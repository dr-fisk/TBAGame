#include "drawable/drawable.h"
#include "renderEngine/renderKey.h"

void Drawable::setRenderId(const uint64_t cRenderId)
{
  mRenderId = cRenderId;
}

void Drawable::registerDrawable(std::shared_ptr<BatchBuffer>& prBatch, const uint32_t cTextureId)
{
  mRenderId = 0;
  mpBatch = prBatch;
  mpBatch->registerDrawable(this, cTextureId, mLayer);
  mNeedUpdate = false;
  mRender = true;
  std::cout << "Render ID: " << mRenderId << " with text id " << cTextureId << std::endl;
}

void Drawable::reregisterDrawable(const uint32_t cTextureId)
{
  mpBatch->registerDrawable(this, RenderKey(mRenderId, cTextureId, mLayer));
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