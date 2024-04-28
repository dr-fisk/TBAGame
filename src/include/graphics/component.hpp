#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "utility/transform.hpp"

#include <functional>

class Component
{
  public:
    virtual ~Component() = default;
    virtual void draw() = 0;
    // virtual void resize(){};
    virtual Component& movePos(const glm::vec2& crMove);
    virtual Component& setPos(const glm::vec2& crPos);
    virtual Component& resize(const glm::vec2& crSize);
    virtual Component& setPadding(const glm::vec2& crPadding);
  protected:
    Transform mTransform;
    glm::vec2 mPadding;
    std::function<void()> mExtraUpdate;
};

#endif