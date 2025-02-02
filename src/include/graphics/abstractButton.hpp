#ifndef ABSTRACT_BUTTON_HPP
#define ABSTRACT_BUTTON_HPP

#include <functional>
#include <list>

#include "graphics/label.hpp"
#include "event/event.hpp"
#include "graphics/itemListener.hpp"
#include "graphics/actionListener.hpp"
#include "event/eventSubscriber.hpp"
#include "input/mouseEvent.hpp"

enum class ButtonState
{
  DEFAULT_STATE,
  HOVER_STATE,
  PRESSED_STATE
};

class AbstractButton : public Component
{
  public:
    AbstractButton();
    virtual ~AbstractButton();
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Setters
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    //! @brief Sets Label
    //!
    //! @param[in] crLabel Label
    //!
    //! @return Abstract Button Reference
    AbstractButton& setLabel(const Label& crLabel);

    AbstractButton& setDefaultTexture(const std::shared_ptr<Texture2D>& crpTexture);
    AbstractButton& setHoverTexture(const std::shared_ptr<Texture2D>& crpTexture);
    AbstractButton& setPressedTexture(const std::shared_ptr<Texture2D>& crpTexture);
    AbstractButton& setDefaultBackgroundColor(const lg::Color& crColor);
    AbstractButton& setHoverBackgroundColor(const lg::Color& crColor);
    AbstractButton& setPressedBackgroundColor(const lg::Color& crColor);
    virtual AbstractButton& movePos(const glm::vec2& crMove) override;
    virtual AbstractButton& setPos(const glm::vec2& crPos)  override;
    virtual AbstractButton& resize(const glm::vec2& crSize) override;
    AbstractButton& setString(const std::string& crString);
    AbstractButton& setPadding(const glm::vec2& crPadding);
    AbstractButton& addItemListener(ItemListener* cpItemListener);
    AbstractButton& addActionListener(ActionListener<AbstractButton>* cpActionListener);
    AbstractButton& setBorder(const float cBorderSize);
    AbstractButton& setBackgroundColor(const ButtonState cState, const lg::Color& crColor);
    AbstractButton& setBorderColor(const ButtonState cState, const lg::Color& crColor);
    void removeActionListener(const ActionListener<AbstractButton>* cpActionListener);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getters
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::string getString() const;
    glm::vec2 getPos() const;
    glm::vec2 getSize() const;

    //! @brief Gets Label
    //!
    //! @return Label Reference to allow modification
    Label& getLabel();
    bool isPressed() const;
    bool isHover() const;
    bool isDefault() const;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Event Handlers
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void handleEvent(const Event& crEvent);
    virtual void draw() override;
    AbstractButton& onClick(std::function<void()> pFunc);
    bool wasClicked() const;
    virtual void updateUI() override;
  protected:
    void onMouseMove(LestRenderEngine::MouseMoveEvent& crEvent);
    void onMouseButtonPress(LestRenderEngine::MouseButtonPressEvent& crEvent);
    void onMouseButtonRelease(LestRenderEngine::MouseButtonReleaseEvent& crEvent);

    void mouseMoveUpdate(const Event::MouseMoveEvent& crEvent);
    void mouseButtonUpdate(const Event::MouseButtonEvent& crEvent);
    void mouseButtonRelease(const Event::MouseButtonEvent& crEvent);
    bool isInAABB(const glm::vec2& crPos);
    bool isInAABB(const glm::vec2& crPos, const glm::vec2& crPadding);
    virtual void setButtonTexture();
    virtual void buttonClicked() = 0;

    Label mLabel;
    std::shared_ptr<Texture2D> mpDefaultTexture;
    std::shared_ptr<Texture2D> mpHoverTexture;
    std::shared_ptr<Texture2D> mpPressedTexture;
    lg::Color mDefaultBackgroundColor;
    lg::Color mHoverBackgroundColor;
    lg::Color mPressedBackgroundColor;
    lg::Color mDefaultBorderColor;
    lg::Color mHoverBorderColor;
    lg::Color mPressedBorderColor;
    ButtonState mState;
    glm::vec2 mPressedPadding;
    std::list<ItemListener*> mItemListeners;
    std::list<ActionListener<AbstractButton>*> mActionListeners;
    std::function<void()> mCallback;
    bool mClicked;
    EventSubscriber<LestRenderEngine::MouseButtonPressEvent> mMouseButtonPressSub;
    EventSubscriber<LestRenderEngine::MouseButtonReleaseEvent> mMouseButtonReleaseSub;
    EventSubscriber<LestRenderEngine::MouseMoveEvent> mMouseMoveSub;
};

#endif