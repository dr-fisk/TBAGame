#ifndef GIF_IMPORTER_HPP
#define GIF_IMPORTER_HPP

#include "animation.hpp"
#include "frameSource.hpp"

class GifImporter
{
public:
  //! @brief Deleted default constructor
  GifImporter() = delete;

  //! @brief Default Destructor
  ~GifImporter() = default;

  //! @brief Builds animation from GIF file path
  //!
  //! @param[in] crGif GIF file path
  //! @param[in] cLoop Loop animation or not
  //!
  //! @return Animation
  static Animation buildAnimation(const std::string& crGif, const bool cLoop = false);

  //! @brief Builds an animated frame source
  //!
  //! @param[in] crGif GIF file path
  //! @param[in] cLoop Loop GIF or not
  //!
  //! @return AnimatedFrameSource shared pointer
  static std::shared_ptr<FrameSource> buildAnimatedFrameSource(const std::string& crGif, const bool cLoop = false);
};

#endif