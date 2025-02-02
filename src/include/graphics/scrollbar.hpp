#ifndef SCROLLBAR_HPP
#define SCROLLBAR_HPP

#include <vector>
#include <memory>

#include "graphics/Component.hpp"
#include "graphics/button.hpp"
#include "glm/vec2.hpp"

class Scrollbar : public Component
{
  public:
    enum ScrollbarOrientation
    {
      HORIZONTAL,
      VERTICAL
    };


    Scrollbar() = delete;
    Scrollbar(const ScrollbarOrientation cOrientation, const uint32_t cMin, const uint32_t cMax);
    ~Scrollbar() = default;
    Scrollbar& setButton(const std::shared_ptr<Button> cpButton);
    void update(const Event& crEvent);
    void draw();

    Scrollbar& addComponent(const std::shared_ptr<Component> pComponent);
    void updateUI() override;
  private:
    void mouseMoveEvent(const Event& crEvent);
    void onMouseMove(LestRenderEngine::MouseMoveEvent& crEvent);


    enum ScrollbarState
    {
      DEFAULT_STATE,
      SCROLL_STATE
    };

    std::shared_ptr<Button> mScrollbarButton;
    glm::vec2 mPrevMousePos;
    ScrollbarState mState;
    ScrollbarOrientation mOrientation;
    std::vector<std::shared_ptr<Component>> mGraphicsList;
    uint32_t mMinBound;
    uint32_t mMaxBound;
    EventSubscriber<LestRenderEngine::MouseMoveEvent> mMouseMoveSub;
};

#endif