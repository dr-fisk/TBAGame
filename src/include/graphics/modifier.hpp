#ifndef MODIFIER_HPP
#define MODIFIER_HPP

#include "color.hpp"
#include "utility/transform.hpp"

enum class HorizontalAlign
{
  LEFT,
  CENTER,
  RIGHT,
  NONE
};

enum class VerticalAlign
{
  TOP,
  CENTER,
  BOTTOM,
  NONE
};

class Modifier
{
  public:
    //! @brief Default constructor
    Modifier() = default;

    //! @brief Sets Background Color
    //!
    //! @param[in] crColor Specified Color
    //!
    //! @return Modifier Reference
    Modifier& setBackGroundColor(const lg::Color& crColor);

    //! @brief Sets the Vertical alignment
    //!
    //! @param[in] cAlign Vertical Alignment 
    //!
    //! @return Modifier Reference 
    Modifier& setVerticalAlign(const VerticalAlign cAlign);

    //! @brief Sets the Horizontal Align
    //!
    //! @param[in] cAlign Horizontal Alignment 
    //!
    //! @return Modifier Reference
    Modifier& setHorizontalAlign(const HorizontalAlign cAlign);

    //! @brief Sets Width
    //!
    //! @param[in] cWidth Width
    //!
    //! @return Modifier Reference
    Modifier& setWidth(const float cWidth);

    //! @brief Sets Height
    //!
    //! @param[in] cHeight Height
    //!
    //! @return Modifier Reference
    Modifier& setHeight(const float cHeight);

    //! @brief Sets X Position
    //!
    //! @param[in] cLeft X Position
    //!
    //! @return Modifier Reference
    Modifier& setLeft(const float cLeft);
    
    //! @brief Sets Top
    //!
    //! @param[in] cTop Top
    //!
    //! @return Modifier Reference
    Modifier& setTop(const float cTop);

    //! @brief Sets the transform position
    //!
    //! @param crPos Position
    //! 
    //! @return Modifier Reference
    Modifier& setPos(const glm::vec2& crPos);

    //! @brief Sets the transform scale
    //!
    //! @param crScale Scale
    //! 
    //! @return Modifier Reference 
    Modifier& setScale(const glm::vec2& crScale);

    //! @brief Sets Rotation
    //!
    //! @param[in] cRotation Rotation
    //!
    //! @return Modifier Reference
    Modifier& setRotation(const float cRotation);

    //! @brief Move transform
    //!
    //! @param[in] crMove Move Vector
    //! 
    //! @return Modifier Reference
    Modifier& moveTransform(const glm::vec2& crMove);

    //! @brief Gets the Background Color
    //!
    //! @return Background Color
    const lg::Color& getBackGroundColor();

    //! @brief Gets the Vertical Alignment
    //!
    //! @return Vertical Alignment 
    VerticalAlign getVerticalAlign();

    //! @brief Gets the Horizontal Alignment
    //!
    //! @return Horizontal Alignment 
    HorizontalAlign getHorizontalAlign();

    //! @brief Gets Width
    //!
    //! @return Width
    float getWidth() const;

    //! @brief Gets Height
    //!
    //! @return Height
    float getHeight() const;

    //! @brief Gets X Position
    //!
    //! @return Left
    float getLeft() const;
    
    //! @brief Gets Top
    //!
    //! @return Top
    float getTop() const;

    //! @brief Gets Rotation
    //!
    //! @return Rotation
    float getRotation() const;

    //! @brief Gets the Position
    //!
    //! @return Position
    glm::vec2 getPos() const;

    //! @brief Gets the Scale
    //!
    //! @return Scale 
    glm::vec2 getScale() const;

    //! @brief Gets the transform
    //!
    //! @return Transform 
    Transform getTransform() const;
  private:
    lg::Color mBackgroundColor;
    VerticalAlign mVerticalAlign = VerticalAlign::TOP;
    HorizontalAlign mHorizontalAlign = HorizontalAlign::LEFT;
    Transform mTransform;
};

#endif