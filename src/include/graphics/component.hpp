#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>
#include <vector>

#include "utility/transform.hpp"
#include "event/event.hpp"
#include "graphics/modifier.hpp"
#include "event/eventDispatcher.hpp"
#include "input/mouseEvent.hpp"
#include "input/keyboardEvent.hpp"
#include "input/windowEvent.hpp"
#include "graphicsEvent/focusEvent.hpp"
#include "graphicsEvent/submitEvent.hpp"

class PopupMenu;

class Component
{
  public:
    using MousePressListener = EventSubscriber<lre::MouseButtonPressEvent>;
    using MouseReleaseListener = EventSubscriber<lre::MouseButtonReleaseEvent>;
    using MouseMoveListener = EventSubscriber<lre::MouseMoveEvent>;
    using KeyPressListener = EventSubscriber<lre::KeyboardPressEvent>;
    using KeyReleaseListener = EventSubscriber<lre::KeyboardReleaseEvent>;
    using FocusEventListener = EventSubscriber<FocusEvent<Component>>;
    using SubmitEventListener = EventSubscriber<SubmitEvent<Component>>;

    //! @brief Default constructor
    Component();

    //! @brief Default destructor
    virtual ~Component();

    virtual void draw() = 0;

    //! @brief Moves the component
    //!
    //! @param[in] crMove Movement vector
    //!
    //! @return Component reference to chain calls
    virtual Component& movePos(const glm::vec2& crMove);

    //! @brief Sets the position of the component
    //!
    //! @param[in] crPos Position
    //!
    //! @return Component reference to chain calls
    virtual Component& setPos(const glm::vec2& crPos);

    //! @brief Resizes the component
    //!
    //! @param[in] crSize Size to set
    //!
    //! @return Component reference to chain calls
    virtual Component& resize(const glm::vec2& crSize);

    //! @brief Sets the padding for the element
    //!
    //! @param[in] crPadding Padding to set
    //!
    //! @return Component reference to chain calls
    virtual Component& setPadding(const glm::vec2& crPadding);
    
    //! @brief Checks if coordinates are within Component bounds
    //!
    //! @param[in] cX X coordinate
    //! @param[in] cY Y coordinate
    //! 
    //! @return true if coordinates are within bounds
    virtual bool contains(const float cX, const float cY);

    //! @brief Adds component to tree
    //!
    //! @param[in] pComponent Component Pointer
    //!
    //! @return Component Reference
    virtual Component& addComponent(std::shared_ptr<Component> pComponent);

    //! @brief Sets Modifier
    //!
    //! @param[in] crModifier Modifier 
    //!
    //! @return Component Reference
    virtual Component& setModifier(const Modifier& crModifier);
    
    //! @brief Shows or hides component
    //!
    //! @param[in] cVisible Boolean to show/hide component
    virtual void setVisible(const bool cVisible);

    //! @brief Enables or disables component
    //!
    //! @param[in] cEnable Boolean to enable/disable component
    void setEnabled(const bool cEnable);

    //! @brief Focuses or unfocuses component
    //!
    //! @param[in] cFocus Boolean to focus/unfocus component
    void setFocus(const bool cFocus);

    //! @brief Checks if component is visible
    //!
    //! @return true if visible false otherwise
    bool isVisible() const;

    //! @brief Returns whether component is enabled or not
    //!
    //! @return True if enabled false otherwise
    bool isEnabled() const;

    //! @brief Returns whether component is focused or not
    //!
    //! @return True if focused false otherwise
    bool isFocused() const;

    //! @brief Gets popup menu associated with component
    //!
    //! @return Popup Menu
    virtual std::shared_ptr<PopupMenu> getPopupMenu() const;
  
    // Perhaps eventually have an event listener to force update all this instead of checking if update is needed
    virtual void updateUI() = 0;

    //! @brief Compares the identity of the component
    //!
    //! @param crComponent Component
    //!
    //! @return true if identity matches
    //! @return false if identity check fails
    bool operator==(const Component& crComponent) const;

    //! @brief Adds MousePressListener
    //!
    //! @param[in] rMousePressListener MousePressListener
    void addMousePressListener(EventSubscriber<lre::MouseButtonPressEvent>& rMousePressListener);

    //! @brief Adds MouseReleaseListener
    //!
    //! @param[in] MouseReleaseListener MouseReleaseListener
    void addMouseReleaseListener(EventSubscriber<lre::MouseButtonReleaseEvent>& rMouseReleaseListener);

    //! @brief Adds MouseMoveListener
    //!
    //! @param[in] rMouseMoveListener MouseMoveListener
    void addMouseMoveListener(EventSubscriber<lre::MouseMoveEvent>& rMouseMoveListener);

    //! @brief Adds KeyPressListener
    //!
    //! @param[in] rKeyPressListener KeyPressListener
    void addKeyPressListener(EventSubscriber<lre::KeyboardPressEvent>& rKeyPressListener);

    //! @brief Adds KeyReleaseListener
    //!
    //! @param[in] rMousePressListener KeyReleaseListener
    void addKeyReleaseListener(EventSubscriber<lre::KeyboardReleaseEvent>& rKeyReleaseListener);

    //! @brief Adds FocusEventListener
    //!
    //! @param[in] rFocusEventListener FocusEventListener
    void addFocusEventListener(FocusEventListener& rFocusEventListener);

    //! @brief Adds SubmitEventListener
    //!
    //! @param[in] rSubmitEventListener SubmitEventListener
    void addSubmitEventListener(SubmitEventListener& rSubmitEventListener);

    //! @brief Gets MousePressListener
    std::vector<MousePressListener*> getMousePressListeners() const;

    //! @brief Gets MouseReleaseListener
    std::vector<MouseReleaseListener*> getMouseReleaseListeners() const;

    //! @brief Gets MouseMoveListener
    std::vector<MouseMoveListener*> getMouseMoveListeners() const;

    //! @brief Gets KeyPressListener
    std::vector<KeyPressListener*> getKeyPressListeners() const;

    //! @brief Gets KeyReleaseListener
    std::vector<KeyReleaseListener*> getKeyReleaseListeners() const;

    //! @brief Get components assigned to this component
    //!
    //! @return Components list
    std::vector<std::shared_ptr<Component>> getComponents() const;

    //! @brief Dispatches events to subcomponents
    //!
    //! @param[in] rEvent Event to dispatch
    virtual void dispatchEvent(I_Event<lre::LestRenderEngineEvents>& rEvent);

  protected:
    //! @brief Processes the event received
    //!
    //! @param[in] rEvent The event to process
    virtual void processEvent(I_Event<lre::LestRenderEngineEvents>&) {}

    glm::vec2 mPadding;
    Modifier mModifier;
    bool mVisible;
    bool mUpdateUI;
    bool mEnabled;
    bool mIsFocused = false;
    uint64_t mID;
    std::vector<std::shared_ptr<Component>> mComponents;
    std::vector<MousePressListener*> mMousePressListeners;
    std::vector<MouseReleaseListener*> mMouseReleaseListeners;
    std::vector<MouseMoveListener*> mMouseMoveListeners;
    std::vector<KeyReleaseListener*> mKeyReleaseListeners;
    std::vector<KeyPressListener*> mKeyPressListeners;
    EventDispatcher<FocusEvent<Component>> mFocusEventDispatcher;
    EventDispatcher<SubmitEvent<Component>> mSubmitEventDispatcher;
};

#endif