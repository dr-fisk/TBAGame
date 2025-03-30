#include "graphics/component.hpp"
#include "graphics/popupMenu.hpp"
#include "graphics/componentManager.hpp"

#include <iostream>

static std::shared_ptr<ComponentManager> gComponentManager;

Component::Component()
{
  mVisible = true;
  mUpdateUI = true;
  mEnabled = true;

  if(!gComponentManager)
  {
    gComponentManager = ComponentManager::getComponentManager();
  }

  gComponentManager->generateID(mID);
}

Component::~Component()
{
  gComponentManager->unregisterComponent(*this);
}

Component& Component::movePos(const glm::vec2& crMove)
{
  mModifier.moveTransform(crMove);
  mUpdateUI = true;
  return *this;
}

Component& Component::setPos(const glm::vec2& crPos)
{
  mModifier.setPos(crPos);
  mUpdateUI = true;

  return *this;
}

Component& Component::resize(const glm::vec2& crSize)
{
  mModifier.setScale(crSize);
  mUpdateUI = true;

  return *this;
}

Component& Component::setPadding(const glm::vec2& crPadding)
{
  mPadding = crPadding;
  mUpdateUI = true;
  
  return *this;
}

void Component::setVisible(const bool cVisible)
{
  mVisible = cVisible;
}

bool Component::isVisible() const
{
  return mVisible;
}

void Component::setEnabled(const bool cEnable)
{
  mEnabled = cEnable;
}

Component& Component::setModifier(const Modifier& crModifier)
{
  mModifier = crModifier;
  mUpdateUI = true;
  return *this;
}

bool Component::isEnabled() const
{
  return mEnabled;
}

std::shared_ptr<PopupMenu> Component::getPopupMenu() const
{
  return nullptr;
}

bool Component::operator==(const Component& crComponent) const
{
  if(this == &crComponent)
  {
    return true;
  }

  return false;
}

Component& Component::addComponent(std::shared_ptr<Component> pComponent)
{
  mComponents.push_back(pComponent);
  return *this;
}

void Component::addMousePressListener(Component::MousePressListener& rMousePressListener)
{
  mMousePressListeners.push_back(&rMousePressListener);
}

void Component::addMouseReleaseListener(Component::MouseReleaseListener& rMouseReleaseListener)
{
  mMouseReleaseListeners.push_back(&rMouseReleaseListener);
}

void Component::addMouseMoveListener(Component::MouseMoveListener& rMouseMoveListener)
{
  mMouseMoveListeners.push_back(&rMouseMoveListener);
}

void Component::addKeyPressListener(Component::KeyPressListener& rKeyPressListener)
{
  mKeyPressListeners.push_back(&rKeyPressListener);
}

void Component::addKeyReleaseListener(Component::KeyReleaseListener& rKeyReleaseListener)
{
  mKeyReleaseListeners.push_back(&rKeyReleaseListener);
}

std::vector<Component::MousePressListener*> Component::getMousePressListeners() const
{
  return mMousePressListeners;
}

std::vector<Component::MouseReleaseListener*> Component::getMouseReleaseListeners() const
{
  return mMouseReleaseListeners;
}

std::vector<Component::MouseMoveListener*> Component::getMouseMoveListeners() const
{
  return mMouseMoveListeners;
}

std::vector<Component::KeyReleaseListener*> Component::getKeyReleaseListeners() const
{
  return mKeyReleaseListeners;
}

std::vector<Component::KeyPressListener*> Component::getKeyPressListeners() const
{
  return mKeyPressListeners;
}

bool Component::contains(const float cX, const float cY)
{
  return mModifier.getTransform().contains(cX, cY);
}

std::vector<std::shared_ptr<Component>> Component::getComponents() const
{
  return  mComponents;
}

void Component::dispatchEvent(I_Event<lre::LestRenderEngineEvents>& rEvent)
{
  for(auto& component : mComponents)
  {
    component->dispatchEvent(rEvent);
  }
  
  if(mVisible)
  {
    processEvent(rEvent);
  }
}