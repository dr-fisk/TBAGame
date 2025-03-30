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
    
    //! @brief Sets Left
    //!
    //! @param[in] cLeft Left
    //! 
    //! @return Transform Reference
    Transform& setLeft(const float cLeft);

    //! @brief Sets Top
    //!
    //! @param[in] cTop Top
    //! 
    //! @return Transform Reference
    Transform& setTop(const float cTop);

    //! @brief Sets Width
    //!
    //! @param[in] cWidth Width
    //! 
    //! @return Transform Reference
    Transform& setWidth(const float cWidth);

    //! @brief Sets Height
    //!
    //! @param[in] cHeight Height
    //! 
    //! @return Transform Reference 
    Transform& setHeight(const float cHeight);

    //! @brief Checks if coordinates are within Transform bounds
    //!
    //! @param[in] cX X coordinate
    //! @param[in] cY Y coordinate
    //! 
    //! @return true if coordinates are within bounds
    //! @return false if not in bounds
    bool contains(const float cX, const float cY);

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