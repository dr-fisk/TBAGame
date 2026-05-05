#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "shapes/rect.hpp"
#include "renderEngine/texture2D.hpp"
#include <vector>
#include <memory>
#include <chrono>

struct AnimationFrame
{
  Rect<float> uv; //!< UV Coordinates for texture
  float DurationS; //!< Duration of each frame
  std::shared_ptr<Texture2D> Texture; //!< Texture associated to frame
};

class Animation
{
public:
  //! @brief Default Constructor
  Animation() = default;

  //! @brief Default Destructor
  ~Animation() = default;

  //! @brief Set the animation render frames
  //!
  //! @brief Animation reference to chain calls
  Animation& setRenderFrames(const std::vector<AnimationFrame>& crRenderFrames);

  //! @brief Returns the current Texture
  //!
  //! @return Current Texture of the frame
  const Texture2D* getCurrentTexture() const;

  //! @brief Returns the current UV coordinates corresonding to the Texture
  //!
  //! @return UV coordinates
  Rect<float> getCurrentUv() const;

  //! @brief Updates the animation
  //!
  //! @param[in] cDt Delta time since last frame
  void update(const float cDt);

  //! @brief Set whether the animation should loop
  //!
  //! @param[in] cLoop true loop, false don't loop
  void shoudLoop(const float cLoop);
private:
  //! Frames for aimation
  std::vector<AnimationFrame> mFrames;
  //! Flag to determine if animation should loop
  bool mLoop = false;

  //! Texture for the animation
  std::shared_ptr<Texture2D> mpTexture;

  //! Current Frame
  size_t mCurrentFrame = 0;

  //! Time since the last update call
  float mDurationS = 0;
};

#endif