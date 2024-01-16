#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "graphics/button.h"
#include "Vector.h"

class Scrollbar
{
  public:
    Scrollbar() = default;
    Scrollbar(std::shared_ptr<RenderEngine>& prRenderEngine, std::shared_ptr<BatchBuffer>& prBatch,
              const Vector2<float>& crPos, const Vector2<float>& crSize);
    ~Scrollbar() = default;
    void setDefaultTexture(const std::shared_ptr<TextureResource>& crpTexture);
    void setHoverTexture(const std::shared_ptr<TextureResource>& crpTexture);
    void setPressedTexture(const std::shared_ptr<TextureResource>& crpTexture);
    void setDefaultColor(const lg::Color& crColor);
    void setHoverColor(const lg::Color& crColor);
    void setPressedColor(const lg::Color& crColor);
    void setPressedPadding(const Vector2<float>& crPadding);
    void update(const Event& crEvent);
  private:
    void mousePressEvent(const Event& crEvent);
    void mouseReleaseEvent(const Event& crEvent);
    void mouseMoveEvent(const Event& crEvent);

    enum ScrollbarState
    {
      DEFAULT_STATE,
      SCROLL_STATE
    };

    std::shared_ptr<Button<>> mScrollbarButton;
    float mPrevMousey;
    ScrollbarState mState;
};

#endif