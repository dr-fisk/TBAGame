#ifndef IMAGE_IMPORTER_HPP
#define IMAGE_IMPORTER_HPP

#include "staticFrameSource.hpp"
#include "image.hpp"

class ImageImporter
{
public:
  //! @brief Deleted Default Constructor
  ImageImporter() = delete;

  //! @brief Default Destructor
  ~ImageImporter() = default;

  //! @brief Builds a static frame from image file path
  //!
  //! @param[in] crImage Image file path
  //!
  //! @return Static Frame Source shared pointer
  static std::shared_ptr<StaticFrameSource> buildStaticFrame(const std::string& crImage);

  //! @brief Builds a texture from image file path
  //!
  //! @param[in] crImage Image file path
  //!
  //! @return texture shared ptr
  static std::shared_ptr<Texture2D> buildTexture(const std::string& crImage);

  //! @brief Builds a Static frame from Image
  //!
  //! @param[in] crImage Image
  //!
  //! @return Static Frame Source shared pointer
  static std::shared_ptr<StaticFrameSource> buildStaticFrame(const Image& crImage);
};

#endif