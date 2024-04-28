#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "common.hpp"
#include "renderEngine/texture2D.hpp"
#include "resource/textureResource.hpp"
#include "glm/vec2.hpp"
#include "renderer/camera.hpp"
#include "shapes/box.hpp"
#include "utility/transform.hpp"

enum PrimitiveType
{
  RECTANGLE, 
  TRIANGLE
};

// TODO: find a way to combine this with graphics class because technically they are all drawables
// Drawable allows drawable items to be held in one container for easy access of render data
class Drawable
{
  public:
    virtual ~Drawable() = default;
    virtual void draw() = 0;
    // virtual Box<glm::vec2> getGlobalBounds(const OrthCamera& crCamera) const;
};

#endif