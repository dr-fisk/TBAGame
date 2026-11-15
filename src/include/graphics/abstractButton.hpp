#ifndef ABSTRACT_BUTTON_HPP
#define ABSTRACT_BUTTON_HPP

#include <functional>
#include <list>

#include "graphics/label.hpp"
#include "event/event.hpp"
#include "event/applicationEventDispatcher.hpp"
#include "graphics/itemListener.hpp"
#include "graphics/actionListener.hpp"
#include "graphicsEvent/guiActionEvent.hpp"
#include "event/eventSubscriber.hpp"
#include "input/mouseEvent.hpp"
#include "resource/frameSource.hpp"

enum class ButtonState
{
  DEFAULT_STATE,
  HOVER_STATE,
  PRESSED_STATE
};

class AbstractButton : public Component
{
  public:
    using ButtonEvent = GuiActionEvent<AbstractButton>;

    AbstractButton();
    AbstractButton(const Modifier& crModifier, const TextModifier& crTextModifier);
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

    //! @brief Attaches Button Event Listener
    //!
    //! @param rListener Button Event Listener
    //!
    //! @return Abstract Button Reference
    AbstractButton& addButtonEventListener(EventSubscriber<ButtonEvent>& rListener);
    
    //! @brief Removes Button Event Listener
    //!
    //! @param rListener Button Event Listener
    //!
    //! @return Abstract Button Reference
    AbstractButton& removeButtonEventListener(EventSubscriber<ButtonEvent>& rListener);
    AbstractButton& setDefaultTexture(const std::shared_ptr<FrameSource> cpFrameSource);
    AbstractButton& setHoverTexture(const std::shared_ptr<FrameSource> cpFrameSource);
    AbstractButton& setPressedTexture(const std::shared_ptr<FrameSource> cpFrameSource);
    AbstractButton& setDefaultBackgroundColor(const lg::Color& crColor);
    AbstractButton& setHoverBackgroundColor(const lg::Color& crColor);
    AbstractButton& setPressedBackgroundColor(const lg::Color& crColor);
    virtual AbstractButton& movePos(const glm::vec2& crMove) override;
    virtual AbstractButton& setPos(const glm::vec2& crPos)  override;
    virtual AbstractButton& resize(const glm::vec2& crSize) override;
    AbstractButton& setString(const std::string& crString);

    //! @brief Sets padding to allow users to click on button
    //!
    //! @param[in] crPadding Padding to set on button 
    //!
    //! @return Abstract Button to chain calls
    AbstractButton& setPadding(const glm::vec2& crPadding);
    AbstractButton& addItemListener(ItemListener* cpItemListener);

    //! @brief Adds action listener to listeners list
    //!
    //! @param[in] pActionListener Listener 
    //!
    //! @return Abstract Button reference to chain calls
    AbstractButton& addActionListener(ActionListener<AbstractButton>* cpActionListener);
    AbstractButton& setBorder(const float cBorderSize);
    AbstractButton& setBackgroundColor(const ButtonState cState, const lg::Color& crColor);

    AbstractButton& setBorderColor(const ButtonState cState, const lg::Color& crColor);

    //! @brief Removes action listener from list
    //!
    //! @param[in] cpActionListener Listener
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

    //! @brief Returns whether Button is pressed
    //!
    //! @return true if pressed, false otherwise 
    bool isPressed() const;

    //! @brief Returns whether Button has mouse hovering over it
    //!
    //! @return true if mouse hovering over button, false otherwise 
    bool isHover() const;

    //! @brief Returns whether Button is in a default state meaning not pressed, not hover
    //!
    //! @return true if button is in default state, false otherwise 
    bool isDefault() const;

    //! @brief Draws Button
    virtual void draw() override;

    AbstractButton& onClick(std::function<void()> pFunc);

    //! @brief Returns whether the button was clicked
    //!
    //! @return true if clicked, false otherwise 
    bool wasClicked() const;
    virtual void updateUI() override;
  protected:
    void onMouseMove(lre::MouseMoveEvent& crEvent);
    void onMouseButtonPress(lre::MouseButtonPressEvent& crEvent);
    void onMouseButtonRelease(lre::MouseButtonReleaseEvent& crEvent);

    bool isInAABB(const glm::vec2& crPos);
    bool isInAABB(const glm::vec2& crPos, const glm::vec2& crPadding);
    virtual void setButtonTexture();
    virtual void buttonClicked() = 0;
    void processEvent(I_Event<lre::LestRenderEngineEvents>& rEvent) override;

    Label mLabel;
    std::shared_ptr<FrameSource> mpDefaultTexture;
    std::shared_ptr<FrameSource> mpHoverTexture;
    std::shared_ptr<FrameSource> mpPressedTexture;
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

    lre::ApplicationEventDispatcher<std::string> mDispatcher;
};

#endif