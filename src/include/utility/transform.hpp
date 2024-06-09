#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"

class Transform
{
  public:
    Transform() = default;
    ~Transform() = default;

    Transform& setRotation(const float cRotation);
    Transform& setPos(const glm::vec2& crPos);
    Transform& setScale(const glm::vec2& crScale);
    glm::vec2 getPos() const;
    glm::vec2 getScale() const;
    float getRotation() const;
    glm::mat4 translate(const glm::vec2& crOffset) const;
    void operator+=(const glm::vec2& rVec2);
  private:
    glm::vec2 mPosition{0, 0};
    glm::vec2 mScale{1, 1};
    float mRotation{0};
};

#endif