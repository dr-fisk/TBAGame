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

    //! @brief Default Destructor Deleted
    Scrollbar() = delete;

    //! @brief Scrollbar Constructor
    //!
    //! @param[in] cOrientation Orientation of the scrollbar Vertical or Horizontal 
    //! @param[in] cMin         Min Coordinates that matches orientation of scrollbar
    //! @param[in] cMax         Max Coordinates that matches orientation of scrollbar
    Scrollbar(const ScrollbarOrientation cOrientation, const uint32_t cMin, const uint32_t cMax);
    
    //! @brief Default Destructor
    ~Scrollbar() = default;

    Scrollbar& setButton(const std::shared_ptr<Button> cpButton);

    //! @brief Draws the scrollbar
    //!
    //! @return None
    void draw();

    //! @brief Adds a component to the scrollbar
    //!
    //! @param[in] pComponent Component to add
    //! 
    //! @return Scrollbar reference to chain event 
    Scrollbar& addComponent(const std::shared_ptr<Component> pComponent);
    
    //! @brief Updates UI Components
    //!
    //! @return None
    void updateUI() override;
  private:
    void moveHandler(AbstractButton::ButtonEvent& rButtonEvent);

    //! @brief Button Event Handler
    //!
    //! @param[in] rButtonEvent Button Event 
    void onButtonEvent(AbstractButton::ButtonEvent& rButtonEvent);

    void processEvent(I_Event<lre::LestRenderEngineEvents>& rEvent) override;
    
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

    EventSubscriber<AbstractButton::ButtonEvent> mButtonClickSub;
    EventSubscriber<lre::MouseMoveEvent> mMouseMoveSub;
};

#endif