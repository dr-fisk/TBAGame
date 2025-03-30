#include <iostream>

#include "graphics/componentManager.hpp"
#include "event/lestRenderEngineEventManager.hpp"

ComponentManager::ComponentManager()
{
  SLOT(mMouseButtonPressSub, ComponentManager::onMouseButtonPressEvent);
  SLOT(mMouseButtonReleaseSub, ComponentManager::onMouseButtonReleaseEvent);
  SLOT(mMouseButtonMoveSub, ComponentManager::onMouseMoveEvent);
  SLOT(mKeyboardPressSub, ComponentManager::onKeyboardPressEvent);
  SLOT(mKeyboardReleaseSub, ComponentManager::onKeyboardReleaseEvent);
  SLOT(mWindowResizeSub, ComponentManager::onWindowResizeEvent);
  mDispatcher.addEventDispatcher<lre::MouseButtonPressEvent>();
  mDispatcher.addEventDispatcher<lre::MouseButtonReleaseEvent>();
  mDispatcher.addEventDispatcher<lre::MouseMoveEvent>();
  mDispatcher.addEventDispatcher<lre::KeyboardPressEvent>();
  mDispatcher.addEventDispatcher<lre::KeyboardReleaseEvent>();
  mDispatcher.addEventDispatcher<lre::WindowResizeEvent>();
}

void ComponentManager::generateID(uint64_t& rID)
{
  rID = mIdCounter;
  mIdCounter ++;
}

std::shared_ptr<ComponentManager> ComponentManager::getComponentManager()
{
  static std::shared_ptr<ComponentManager> component_mngr(new ComponentManager);
  return component_mngr;
}

void ComponentManager::registerComponent(Component& rComponent)
{
  mComponents.push_back(&rComponent);
}

void ComponentManager::unregisterComponent(Component& rComponent)
{
  for(auto itr = mComponents.begin(); itr != mComponents.end();)
  {
    if(&rComponent ==  *itr)
    {
      itr = mComponents.erase(itr);
    }
    else
    {
      itr++;
    }
  }
}

void ComponentManager::onMouseButtonPressEvent(lre::MouseButtonPressEvent& rMouseButtonPressEvent)
{
  lre::MouseButtonPressEvent event = rMouseButtonPressEvent;
  for(auto& component : mComponents)
  {
    if(event.isHandled())
    {
      break;
    }
      component->dispatchEvent(event);
  }
}

void ComponentManager::onMouseButtonReleaseEvent(lre::MouseButtonReleaseEvent& rMouseButtonReleaseEvent)
{
  lre::MouseButtonReleaseEvent event = rMouseButtonReleaseEvent;
  for(auto& component : mComponents)
  {
      component->dispatchEvent(event);
  }
}

void ComponentManager::onMouseMoveEvent(lre::MouseMoveEvent& rMouseMoveEvent)
{
  lre::MouseMoveEvent event = rMouseMoveEvent;
  for(auto& component : mComponents)
  {
      component->dispatchEvent(event);
  }
}

void ComponentManager::onKeyboardPressEvent(lre::KeyboardPressEvent& rKeyboardPressEvent)
{
  lre::KeyboardPressEvent event = rKeyboardPressEvent;
  mDispatcher.dispatch(event);
}

void ComponentManager::onKeyboardReleaseEvent(lre::KeyboardReleaseEvent& rKeyboardReleaseEvent)
{
  lre::KeyboardReleaseEvent event = rKeyboardReleaseEvent;
  mDispatcher.dispatch(event);
}

void ComponentManager::onWindowResizeEvent(lre::WindowResizeEvent& rWindowResizeEvent)
{
  lre::WindowResizeEvent event = rWindowResizeEvent;
  mDispatcher.dispatch(event);
}