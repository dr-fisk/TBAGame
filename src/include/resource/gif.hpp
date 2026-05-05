#ifndef GIF_HPP
#define GIF_HPP

#include "resource/animation.hpp"
#include "renderEngine/texture2D.hpp"

#include <memory>
#include <vector>

class Gif
{
public:
  //! @brief Default Constructor
  Gif() = default;

  //! @brief Default Destructor
  ~Gif() = default;

  //! @brief Loads in a GIF file
  //!
  //! @param[in] crGif GIF file path
  //!
  //! @retval -1 on Failure
  //! @retval 0 on Success
  int load(const std::string& crGif);

  //! @brief Gets the render frames of the gif
  //!
  //! @return Render Frame Vector
  std::vector<AnimationFrame> getRenderFrames() const;

  private:
  //! Animation Frames
  std::vector<AnimationFrame> mGifFrames;
};

#endif