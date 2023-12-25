#include "resource/image.h"

Image::Image(const std::string& crPath)
{
  Png::IHDR ihdr;
  Png png(crPath);
  mPixelData = png.getImgData();
  ihdr = png.getIhdr();
  mDimensions = Vector2<int32_t>(ihdr.width, ihdr.height);
}