#ifndef DROP_DOWN_MENU_HPP
#define DROP_DOWN_MENU_HPP

//TODO Rename to dropdown menu

#include <memory>
#include <vector>

#include "graphics/menuItem.hpp"
#include "shapes/box2D.hpp"
#include "graphics/menuListener.hpp"
#include "graphics/popupMenu.hpp"
#include "graphics/popupMenuListener.hpp"

class DropdownMenu : public MenuItem, public MenuListener, public PopupMenuListener
{
  public:
    DropdownMenu();
    ~DropdownMenu() = default;
    void addMenuItem(const std::shared_ptr<MenuItem> cpMenuItem);
    void handleEvent(const Event& crEvent) override;
    void draw() override;
    DropdownMenu& setMenuLocation(const glm::vec2& crPos);
    void performAction(const ActionEvent& crEvent) override;
    void menuDeselected(const MenuEvent& crEvent) override;
    void menuSelected(const MenuEvent& crEvent) override;
    void menuCancelled(const MenuEvent& crEvent) override;
    DropdownMenu& addMenuListener(MenuListener* pListener);
    void removeMenuListener(const MenuListener* cpListener);
    void setIsTopLevel(const bool cTop);
    bool isTopLevel() const;
    std::shared_ptr<PopupMenu> getPopupMenu() const override;
    void popupMenuCancelled(const PopupMenuEvent& crEvent) override;
    void popupMenuWillBecomeInvisible(const PopupMenuEvent& crEvent) override;
    void popupMenuWillBecomeVisible(const PopupMenuEvent& crEvent) override;
    bool isPopupMenuVisible() const;
  private:
    void notifyMenuSelected();
    void notifyMenuDeselected();
    void notifyMenuCancelled();
    // void addMenuItem(const std::shared_ptr<DropdownMenu> cpMenu);

    enum DropDownMenuState
    {
      MENU_LIST_SHOW,
      MENU_LIST_HIDE
    };

    std::shared_ptr<PopupMenu> mpPopupMenu;
    DropDownMenuState mDropDownState;
    Box2D<float> mMenuBounds;
    bool mDefaultMenuLocation;
    std::vector<MenuListener*> mMenuListeners;
    bool mTopLevel;
};

#endif