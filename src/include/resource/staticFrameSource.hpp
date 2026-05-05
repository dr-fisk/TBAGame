#ifndef STATIC_FRAME_SOURCE_HPP
#define STATIC_FRAME_SOURCE_HPP

#include "frameSource.hpp"
#include <memory>

class StaticFrameSource : public FrameSource
{
public:
  //! @brief Default Constructor
  StaticFrameSource() = default;

  //! @brief Default Destructor
  ~StaticFrameSource() = default;

  //! @brief Sets the texture for the Static Frame
  //!
  //! @param[in] crTexture Texture to set
  //!
  //! @return Reference to chain calls
  StaticFrameSource& setTexture(const std::shared_ptr<Texture2D> cpTexture);

  //! @brief Sets the UV for the Static Frame
  //! @note: If not set, the UV will be the (0,0)
  //!
  //! @param[in] crUv UV coordinates
  //!
  //! @return Reference to chain calls
  StaticFrameSource& setUv(const Rect<float>& crUv);

  //! @brief Returns the current Texture
  //!
  //! @return Current Texture of the frame
  const Texture2D* getCurrentTexture() const override;

  //! @brief Returns the current UV coordinates corresonding to the Texture
  //!
  //! @return UV coordinates
  Rect<float> getCurrentUv() const override;

  //! @brief Updates the Frame
  //!
  //! @param[in] cDt Delta time since last frame
  void update(const float cDt) override;
private:
  //! UV coordinates
  //! UV means the position and dimensions within the texture
  Rect<float> mUv;

  //! Current Texture
  std::shared_ptr<Texture2D> mpTexture;
};

#endif