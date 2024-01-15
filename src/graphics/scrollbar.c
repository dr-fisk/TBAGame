#include "graphics/scrollbar.h"

//! @brief 
//! @param prRenderEngine 
//! @param prBatch 
//! @param crPos 
//! @param crSize
//!
//! @return None
Scrollbar::Scrollbar(std::shared_ptr<RenderEngine>& prRenderEngine, std::shared_ptr<BatchBuffer>& prBatch,
                     const Vector2<float>& crPos, const Vector2<float>& crSize)
{
  mScrollbarButton = std::make_shared<Button<>>(prRenderEngine, prBatch, crPos, crSize);
}

void Scrollbar::setDefaultTexture(const std::shared_ptr<TextureResource>& crpTexture)
{
  mScrollbarButton->setDefaultTexture(crpTexture);
}

void Scrollbar::setHoverTexture(const std::shared_ptr<TextureResource>& crpTexture)
{
  mScrollbarButton->setHoverTexture(crpTexture);
}

void Scrollbar::setPressedTexture(const std::shared_ptr<TextureResource>& crpTexture)
{
  mScrollbarButton->setPressedTexture(crpTexture);
}

void Scrollbar::setDefaultColor(const lg::Color& crColor)
{
  mScrollbarButton->setDefaultColor(crColor);
}

void Scrollbar::setHoverColor(const lg::Color& crColor)
{
  mScrollbarButton->setHoverColor(crColor);
}

void Scrollbar::setPressedColor(const lg::Color& crColor)
{
  mScrollbarButton->setPressedColor(crColor);
}
