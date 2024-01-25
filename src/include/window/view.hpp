#ifndef VIEW_HPP
#define VIEW_HPP

#include "glm/vec2.hpp"

class View
{
  public:
    View() = default;
    ~View() = default;
    void setViewPort(const glm::ivec2& crPos, const glm::ivec2& crDimensions);
  private:
    glm::ivec2 mDimensions;
    glm::ivec2 mPos;
};

#endif