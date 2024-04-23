#ifndef SCROLLBAR_HPP
#define SCROLLBAR_HPP

#include <vector>
#include <memory>

#include "graphics/graphics.hpp"
#include "graphics/button.hpp"
#include "glm/vec2.hpp"

class Scrollbar : public Graphics
{
  public:
    Scrollbar() = delete;
    Scrollbar(const Box<glm::vec2>& crBox);
    ~Scrollbar() = default;
    Scrollbar& setDefaultTexture(const std::shared_ptr<Texture2D>& crpTexture);
    Scrollbar& setHoverTexture(const std::shared_ptr<Texture2D>& crpTexture);
    Scrollbar& setPressedTexture(const std::shared_ptr<Texture2D>& crpTexture);
    Scrollbar& setDefaultColor(const lg::Color& crColor);
    Scrollbar& setHoverColor(const lg::Color& crColor);
    Scrollbar& setPressedColor(const lg::Color& crColor);
    Scrollbar& setPressedPadding(const glm::vec2& crPadding);
    Scrollbar& setButton(std::shared_ptr<Button<>>& crpButton);
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