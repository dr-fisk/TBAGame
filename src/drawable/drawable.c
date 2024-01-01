#include "drawable/drawable.h"

void Drawable::setRenderId(const uint64_t cRenderId)
{
  mRenderId = cRenderId;
}

void Drawable::registerDrawable(std::shared_ptr<BatchBuffer>& prBatch, const uint32_t cTextureId)
{
  mRenderId = 0;
  mpBatch = prBatch;
  mpBatch->registerDrawable(this, cTextureId);
  mNeedUpdate = false;
}

uint64_t Drawable::getRenderId()
{
  return mRenderId;
}