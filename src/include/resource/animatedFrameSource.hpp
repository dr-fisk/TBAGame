#ifndef ANIMATED_FRAME_SOURCE_HPP
#define ANIMATED_FRAME_SOURCE_HPP

#include "resource/animation.hpp"
#include "frameSource.hpp"

class AnimatedFrameSource : public FrameSource
{
public:
  //! @brief Default Constructor
  AnimatedFrameSource() = default;

  //! @brief Default Destructor
  ~AnimatedFrameSource() = default;

  //! @brief Sets the animation
  //!
  //! @param[in] crAnimation Animation
  //!
  //! @return AnimatedFrameSource reference to chain calls
  AnimatedFrameSource& setAnimation(const Animation& crAnimation);

  //! @brief Returns the current Texture
  //!
  //! @return Current Texture of the frame
  Texture2D* getCurrentTexture() const override;

  //! @brief Returns the current UV coordinates corresonding to the Texture
  //!
  //! @return UV coordinates
  Rect<float> getCurrentUv() const override;

  //! @brief Updates the Frame
  //!
  //! @param[in] cDt Delta time since last frame
  void update(const float cDt) override;
private:
  Animation mAnimation;
};

#endif