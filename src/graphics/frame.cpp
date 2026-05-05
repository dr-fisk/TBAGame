#include "graphics/frame.hpp"
#include "graphics/componentManager.hpp"

static std::shared_ptr<ComponentManager> gComponentManager;

Frame::Frame()
{
  if(!gComponentManager)
  {
    gComponentManager = ComponentManager::getComponentManager();
  }

  mEDTMousePressListener.setCallback(BIND_EVENT_FN(Frame::onMousePress));
  mEDTMouseReleaseListener.setCallback(BIND_EVENT_FN(Frame::onMouseRelease));
  mEDTMouseMoveListener.setCallback(BIND_EVENT_FN(Frame::onMouseMove));
  mEDTKeyPressListener.setCallback(BIND_EVENT_FN(Frame::onKeyPress));
  mEDTKeyReleaseListener.setCallback(BIND_EVENT_FN(Frame::onKeyRelease));

  gComponentManager->registerComponent(*this);
}

void Frame::draw()
{
  
}

Frame& Frame::addComponent(std::shared_ptr<Component> pComponent)
{
  mComponents.push_back(pComponent);

  return *this;
}

void Frame::onMousePress(lre::MouseButtonPressEvent&)
{
  // if(mVisible)
  // for(auto& component : mComponents)
  // {
  //   if(component->isVisible() && component->contains(event.getX(), event.getY()))
  //   {
  //     component->dispatchEvent(event);
  //   }
  // }
}

void Frame::onMouseRelease(lre::MouseButtonReleaseEvent&)
{

}

void Frame::onMouseMove(lre::MouseMoveEvent&)
{

}

void Frame::onKeyPress(lre::KeyboardPressEvent&)
{

}

void Frame::onKeyRelease(lre::KeyboardReleaseEvent&)
{

}
