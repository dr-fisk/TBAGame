#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <vector>
#include <memory>

#include "graphics/graphics.h"
#include "graphics/button.h"
#include "glm/vec2.hpp"

class Scrollbar : public Graphics
{
  public:
    Scrollbar() = default;
    Scrollbar(std::shared_ptr<RenderEngine>& prRenderEngine, const glm::vec2& crPos, const glm::vec2& crSize);
    ~Scrollbar() = default;
    void setDefaultTexture(const std::shared_ptr<TextureResource>& crpTexture);
    void setHoverTexture(const std::shared_ptr<TextureResource>& crpTexture);
    void setPressedTexture(const std::shared_ptr<TextureResource>& crpTexture);
    void setDefaultColor(const lg::Color& crColor);
    void setHoverColor(const lg::Color& crColor);
    void setPressedColor(const lg::Color& crColor);
    void setPressedPadding(const glm::vec2& crPadding);
    void update(const Event& crEvent);
    void draw();
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
    std::vector<std::shared_ptr<Graphics>> mGraphicsList;
};

#endif