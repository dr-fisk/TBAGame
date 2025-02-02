#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>

#include "utility/transform.hpp"
#include "event/event.hpp"
#include "graphics/modifier.hpp"

class PopupMenu;

class Component
{
  public:
    Component();
    virtual ~Component() = default;
    virtual void draw() = 0;
    virtual Component& movePos(const glm::vec2& crMove);
    virtual Component& setPos(const glm::vec2& crPos);
    virtual Component& resize(const glm::vec2& crSize);
    virtual Component& setPadding(const glm::vec2& crPadding);

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
  protected:
    glm::vec2 mPadding;
    Modifier mModifier;
    bool mVisible;
    bool mUpdateUI;
    bool mEnabled;
};

#endif