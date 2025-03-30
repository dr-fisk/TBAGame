#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include <memory>
#include "component.hpp"
#include "event/applicationEventDispatcher.hpp"
#include "event/lestRenderEngineEvent.hpp"
#include "input/mouseEvent.hpp"
#include "input/keyboardEvent.hpp"
#include "input/windowEvent.hpp"

//! @brief Singleton Component manager to dispatch events and manage components
class ComponentManager
{
  public:
    //! @brief Default Destructor
    ~ComponentManager() = default;

    //! @brief Adds Component to the global component manager
    //! 
    //! @param[in] rComponent Component to add
    //!
    //! @return None
    void registerComponent(Component& rComponent);

    //! @brief Unregisters the component from global component manager
    //!
    //! @param[in] rComponent Component to unregister
    //!
    //! @return None 
    void unregisterComponent(Component& rComponent);

    //! @brief Adds an event listener to the manager
    //!
    //! @tparam T LestRenderEngineEvents
    //! @param[in] rSub Listener to add 
    //!
    //! @return None
    template <typename T>
    void addEventListener(EventSubscriber<T>& rSub)
    {
      rSub.setUnregisterFunc(BIND_EVENT_FN(ComponentManager::removeEventListener<T>));
      mDispatcher.attach(rSub);
    }

    //! @brief Removes event listener from the manager
    //!
    //! @tparam T LestRenderEngineEvents
    //! @param[in] rSub Listener to remove 
    //!
    //! @return true on successful removal
    //! @return false on unsucessful removal
    template <typename T>
    bool removeEventListener(const EventSubscriber<T>& rSub)
    {
      mDispatcher.detach(rSub);
      //Probs add some checks
      return true;
    }

    //! @brief Gets component manager singleton
    //!
    //! @return component manager singleton
    static std::shared_ptr<ComponentManager> getComponentManager();

    //! @brief Generates ID
    //!
    //! @param[in] rID ID generated
    //!
    //! @return None
    void generateID(uint64_t& rID);
  private:
    //! @brief Private Default constructor
    ComponentManager();

    //! @brief MouseButtonPressEvent Handler
    //!
    //! @param[in] rMouseButtonPressEvent MouseButtonPressEvent
    //!
    //! @return None 
    void onMouseButtonPressEvent(lre::MouseButtonPressEvent& rMouseButtonPressEvent);

    //! @brief MouseButtonReleaseEvent Handler
    //!
    //! @param[in] rMouseButtonReleaseEvent MouseButtonReleaseEvent
    //!
    //! @return None 
    void onMouseButtonReleaseEvent(lre::MouseButtonReleaseEvent& rMouseButtonReleaseEvent);

    //! @brief MouseMoveEvent Handler
    //!
    //! @param[in] rMouseMoveEvent MouseMoveEvent
    //!
    //! @return None 
    void onMouseMoveEvent(lre::MouseMoveEvent& rMouseMoveEvent);

    //! @brief KeyboardPressEvent Handler
    //!
    //! @param[in] rKeyboardPressEvent KeyboardPressEvent
    //!
    //! @return None 
    void onKeyboardPressEvent(lre::KeyboardPressEvent& rKeyboardPressEvent);

    //! @brief KeyboardReleaseEvent Handler
    //!
    //! @param[in] rKeyboardReleaseEvent KeyboardReleaseEvent
    //!
    //! @return None 
    void onKeyboardReleaseEvent(lre::KeyboardReleaseEvent& rKeyboardReleaseEvent);

    //! @brief WindowResizeEvent Handler
    //!
    //! @param[in] rWindowResizeEvent WindowResizeEvent
    //!
    //! @return None 
    void onWindowResizeEvent(lre::WindowResizeEvent& rWindowResizeEvent);

    uint64_t mIdCounter = 0;
    std::vector<Component*> mComponents;
    lre::ApplicationEventDispatcher<lre::LestRenderEngineEvents> mDispatcher;
    EventSubscriber<lre::MouseButtonPressEvent> mMouseButtonPressSub;
    EventSubscriber<lre::MouseButtonReleaseEvent> mMouseButtonReleaseSub;
    EventSubscriber<lre::MouseMoveEvent> mMouseButtonMoveSub;
    EventSubscriber<lre::KeyboardPressEvent> mKeyboardPressSub;
    EventSubscriber<lre::KeyboardReleaseEvent> mKeyboardReleaseSub;
    EventSubscriber<lre::WindowResizeEvent> mWindowResizeSub;
};

#endif