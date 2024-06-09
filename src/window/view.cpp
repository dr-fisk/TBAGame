#include "window/view.hpp"

void View::setViewPort(const glm::ivec2& crPos, const glm::ivec2& crDimensions)
{
  mPos = crPos;
  mDimensions = crDimensions;
}