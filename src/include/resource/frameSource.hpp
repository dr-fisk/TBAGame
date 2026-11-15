#ifndef FRAME_SOURCE_HPP
#define FRAME_SOURCE_HPP

#include "renderEngine/texture2D.hpp"
#include "shapes/rect.hpp"

class FrameSource
{
public:
  //! @brief Default Constructor
  FrameSource() = default;

  //! @brief Default Destructor
  ~FrameSource() = default;

  //! @brief Returns the current Texture
  //!
  //! @return Current Texture of the frame
  virtual Texture2D* getCurrentTexture() const = 0;

  //! @brief Returns the current UV coordinates corresonding to the Texture
  //!
  //! @return UV coordinates
  virtual Rect<float> getCurrentUv() const = 0;

  //! @brief Updates the Frame
  //!
  //! @param[in] cDt Delta time since last frame
  virtual void update(const float cDt) = 0;
private:
};

#endif