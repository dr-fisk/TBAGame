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

class PopupMenu;

class Component
{
  public:
    using MousePressListener = EventSubscriber<lre::MouseButtonPressEvent>;
    using MouseReleaseListener = EventSubscriber<lre::MouseButtonReleaseEvent>;
    using MouseMoveListener = EventSubscriber<lre::MouseMoveEvent>;
    using KeyPressListener = EventSubscriber<lre::KeyboardPressEvent>;
    using KeyReleaseListener = EventSubscriber<lre::KeyboardReleaseEvent>;

    Component();
    virtual ~Component();
    virtual void draw() = 0;
    virtual Component& movePos(const glm::vec2& crMove);
    virtual Component& setPos(const glm::vec2& crPos);
    virtual Component& resize(const glm::vec2& crSize);
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
    
    virtual void setVisible(const bool cVisible);
    virtual void setEnabled(const bool cEnable);
    virtual bool isVisible() const;
    virtual bool isEnabled() const;
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
    //!
    //! @return None
    void addMousePressListener(EventSubscriber<lre::MouseButtonPressEvent>& rMousePressListener);

    //! @brief Adds MouseReleaseListener
    //!
    //! @param[in] MouseReleaseListener MouseReleaseListener
    //!
    //! @return None
    void addMouseReleaseListener(EventSubscriber<lre::MouseButtonReleaseEvent>& rMouseReleaseListener);

    //! @brief Adds MouseMoveListener
    //!
    //! @param[in] rMouseMoveListener MouseMoveListener
    //!
    //! @return None
    void addMouseMoveListener(EventSubscriber<lre::MouseMoveEvent>& rMouseMoveListener);

    //! @brief Adds KeyPressListener
    //!
    //! @param[in] rKeyPressListener KeyPressListener
    //!
    //! @return None
    void addKeyPressListener(EventSubscriber<lre::KeyboardPressEvent>& rKeyPressListener);

    //! @brief Adds KeyReleaseListener
    //!
    //! @param[in] rMousePressListener KeyReleaseListener
    //!
    //! @return None
    void addKeyReleaseListener(EventSubscriber<lre::KeyboardReleaseEvent>& rKeyReleaseListener);

    //! @brief Gets MousePressListeners
    //!
    //! @return List of MousePressListeners 
    std::vector<MousePressListener*> getMousePressListeners() const;

    //! @brief Gets MouseReleaseListener
    //!
    //! @return List of MouseReleaseListener
    std::vector<MouseReleaseListener*> getMouseReleaseListeners() const;

    //! @brief Gets MouseMoveListener
    //!
    //! @return List of MouseMoveListener
    std::vector<MouseMoveListener*> getMouseMoveListeners() const;

    //! @brief Gets KeyReleaseListener
    //!
    //! @return List of KeyReleaseListener
    std::vector<KeyReleaseListener*> getKeyReleaseListeners() const;

    //! @brief Gets KeyPressListener
    //!
    //! @return List of KeyPressListener
    std::vector<KeyPressListener*> getKeyPressListeners() const;

    //! @brief Get components assigned to this component
    //!
    //! @return Components list
    std::vector<std::shared_ptr<Component>> getComponents() const;

    virtual void dispatchEvent(I_Event<lre::LestRenderEngineEvents>& rEvent);

  protected:
    virtual void processEvent(I_Event<lre::LestRenderEngineEvents>& rEvent) {}

    glm::vec2 mPadding;
    Modifier mModifier;
    bool mVisible;
    bool mUpdateUI;
    bool mEnabled;
    uint64_t mID;
    std::vector<std::shared_ptr<Component>> mComponents;
    std::vector<MousePressListener*> mMousePressListeners;
    std::vector<MouseReleaseListener*> mMouseReleaseListeners;
    std::vector<MouseMoveListener*> mMouseMoveListeners;
    std::vector<KeyReleaseListener*> mKeyReleaseListeners;
    std::vector<KeyPressListener*> mKeyPressListeners;
};

#endif