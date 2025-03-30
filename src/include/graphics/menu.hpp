#ifndef DROP_DOWN_MENU_HPP
#define DROP_DOWN_MENU_HPP

//TODO Rename to dropdown menu

#include <memory>
#include <vector>

#include "graphics/menuItem.hpp"
#include "shapes/box2D.hpp"
#include "graphics/popupMenu.hpp"

class Menu : public MenuItem
{
  public:
  
    //! @brief Default Constructor
    //!
    //! @return None
    Menu();

    //! @brief Default Destructor
    ~Menu() = default;

    //! @brief Adds a Menu Item to the Popup Menu
    //!
    //! @param[in] cpMenuItem Menu Item to be added
    //!
    //! @return None
    void addMenuItem(const std::shared_ptr<MenuItem> cpMenuItem);
    
    //! @brief Draws the Menu
    //!
    //! @return None
    void draw() override;
    
    //! @brief Sets the Popup Menu location TopLeft pos
    //!
    //! @param[in] crPos Position to set Popup Menu
    //!
    //! @return Menu reference to chain call
    Menu& setMenuLocation(const glm::vec2& crPos);

    //! @brief Sets whether this is a top level menu
    //! TODO: find a better way to do this
    //!
    //! @return None
    void setIsTopLevel(const bool cTop);

    //! @brief Returns if this Menu is Top Level
    //!
    //! @return true if is Top Level, false otherwise
    bool isTopLevel() const;

    //! @brief Returns the Popup Menu assign to this Menu
    //!
    //! @return Popup Menu pointer 
    std::shared_ptr<PopupMenu> getPopupMenu() const override;
    
    //! @brief Gets whether the Popup Menu is visible
    //!
    //! @return true if Popup Menu is visible, false otherwise 
    bool isPopupMenuVisible() const;

    //! @brief Gets the Menu Item list
    //!
    //! @return Menu Items
    std::vector<std::shared_ptr<MenuItem>> getMenuItems() const override;
    void updateUI() override;
  private:
    //! @brief Performs Menu Specific action upon being clicked
    //!
    //! @param[in] crEvent Action Event
    //!
    //! @return None
    void buttonClicked() override;

    //! @brief ButtonEvent Handler
    //!
    //! @param[out] rButtonEvent Button Event
    //!
    //! @return None 
    void onButtonEvent(AbstractButton::ButtonEvent& rButtonEvent);

    //! @brief PopupMenuEvent Handler
    //!
    //! @param[out] rPopupMenuEvent PopupMenu Event
    //!
    //! @return None 
    void onPopupMenuEvent(PopupMenu::PopupMenuEvent& rPopupMenuEvent);

    //! @brief Dispatches events if handled
    //!
    //! @param[out] rEvent Event to handle
    //!
    //! @return None 
    void dispatchEvent(I_Event<lre::LestRenderEngineEvents>& rEvent) override;

    //! TODO: Remove, might not be used anymore
    enum DropDownMenuState
    {
      MENU_LIST_SHOW,
      MENU_LIST_HIDE
    };

    std::shared_ptr<PopupMenu> mpPopupMenu;
    DropDownMenuState mDropDownState;
    Box2D<float> mMenuBounds;
    bool mDefaultMenuLocation;
    bool mTopLevel;

    EventSubscriber<AbstractButton::ButtonEvent> mButtonEventSub;
    EventSubscriber<PopupMenu::PopupMenuEvent> mPopupMenuEventSub;
};

#endif