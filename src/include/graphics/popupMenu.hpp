#ifndef POPUP_MENU_HPP
#define POPUP_MENU_HPP

#include <vector>
#include <memory>

#include "graphics/component.hpp"
#include "graphics/menuItem.hpp"
#include "shapes/box2D.hpp"
#include "graphicsEvent/menuActionEvent.hpp"
#include "event/eventDispatcher.hpp"

class PopupMenu : public Component
{
  public:
    using PopupMenuEvent = MenuActionEvent<PopupMenu>;
    
    //! @brief Default Constructor
    //!
    //! @return PopupMenu Object
    PopupMenu();

    //! @brief Default Destructor
    ~PopupMenu() = default;
    
    //! @brief Adds a menu item to the Popup Menu
    //!        Note: Popup Menu keeps a shared pointer so it is not necessary to keep the menu item in scope
    //!
    //! @param[in] cpMenuItem Menu Item to add to the Popup Menu
    //!
    //! @return None
    void addItem(const std::shared_ptr<MenuItem> cpMenuItem);

    //! @brief Draws the Popup Menu if it is visible
    //!
    //! @return None
    void draw() override;

    //! @brief Sets the preferred size of all Popup Menu Items
    //!
    //! @param[in] cWidth  Width to set Menu Items
    //! @param[in] cHeight Height to set Menu Items
    //!
    //! @return Popup Menu reference to chain calls
    PopupMenu& setPreferredSize(const float cWidth, const float cHeight);

    //! @brief Sets the Popup Menu location
    //!
    //! @param[in] crPos Position to set the Popup Menu
    //!
    //! @return None 
    void setMenuLocation(const glm::vec2& crPos);

    //! @brief Adds PopupMenuEvent listener
    //!
    //! @param rListener PopupMenuEvent Listener
    //!
    //! @return None
    PopupMenu& addPopupMenuListener(EventSubscriber<PopupMenuEvent>& rListener);

    //! @brief Sets the component to be visible or not and notifies listeners
    //!
    //! @param cVisible Controls visibility of component
    //!
    //! @return None
    void setVisible(const bool cVisible) override;

    //! @brief Gets the Menu Item list
    //!
    //! @return Menu Items
    std::vector<std::shared_ptr<MenuItem>> getMenuItems() const;

    //! @brief Updates UI components
    //!
    //! @return None
    void updateUI() override;

    //! @brief Dispatches events if handled
    //!
    //! @param[out] rEvent Event to handle
    //!
    //! @return None 
    void dispatchEvent(I_Event<lre::LestRenderEngineEvents>& rEvent) override;

  private:
    //! @brief Updates the position of the menu items in the PopupMenu
    //!
    //! @return None
    void updatePopupMenuItemPositions();

    //! @brief Notifies listeners that the Popup Menu was cancelled
    //!
    //! @return None
    void notifyCancelled();
    // void notifyInvisible();

    //! @brief Notifies the listeners that the Popup Menu will be visible soon
    //!
    //! @return None
    void notifyVisible();

    //! @brief PopupMenuEvent Handler
    //!
    //! @param[in] rPopupMenuEvent PopupMenuEvent
    //!
    //! @return None
    void onPopupMenuEvent(PopupMenuEvent& rPopupMenuEvent);

    //! @brief ButtonEvent Handler
    //!
    //! @param[in] rButtonEvent ButtonEvent
    //!
    //! @return None
    void onButtonEvent(AbstractButton::ButtonEvent& rButtonEvent);

    std::vector<std::shared_ptr<MenuItem>> mItems;
    Box2D<float> mBounds;
    glm::vec2 mPreferredSize;
    const AbstractButton* cmpInvoker;
    PopupMenu* mActiveSubMenu;

    EventSubscriber<AbstractButton::ButtonEvent> mButtonEventSub;
    EventSubscriber<PopupMenuEvent> mPopupEventSub;
    EventDispatcher<PopupMenuEvent> mDispatcher;
};

#endif