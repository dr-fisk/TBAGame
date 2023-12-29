#include "drawable/drawable.h"

Drawable::Drawable(std::shared_ptr<BatchBuffer>& prBatch)
{
  mRenderId = 0;
  mpBatch = prBatch;
  mpBatch->registerDrawable(this);
  mNeedUpdate = false;
  std::cout << mRenderId << " Constructed" << std::endl;
}

Drawable::~Drawable()
{
  if(0 != mRenderId)
  {
    std::cout << mRenderId << " Destructor called\n";
    mpBatch->unregisterDrawable(mRenderId);
  }
}