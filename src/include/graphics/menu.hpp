#ifndef DROP_DOWN_MENU_HPP
#define DROP_DOWN_MENU_HPP

//TODO Rename to dropdown menu

#include <memory>
#include <vector>

#include "graphics/menuItem.hpp"
#include "shapes/box2D.hpp"
#include "graphics/menuListener.hpp"
#include "graphics/popupMenuListener.hpp"
#include "graphics/popupMenu.hpp"

class Menu : public MenuItem, public PopupMenuListener<PopupMenu>
{
  public:
    Menu();
    ~Menu() = default;
    void addMenuItem(const std::shared_ptr<MenuItem> cpMenuItem);
    void handleEvent(const Event& crEvent) override;
    void draw() override;
    Menu& setMenuLocation(const glm::vec2& crPos);
    Menu& addMenuListener(MenuListener* pListener);
    void removeMenuListener(const MenuListener* cpListener);
    void setIsTopLevel(const bool cTop);
    bool isTopLevel() const;
    std::shared_ptr<PopupMenu> getPopupMenu() const override;
    bool isPopupMenuVisible() const;
    void popupMenuCancelled(const PopupMenuEvent<PopupMenu>& crEvent) override;
    void popupMenuWillBecomeInvisible(const PopupMenuEvent<PopupMenu>& crEvent) override;
    void popupMenuWillBecomeVisible(const PopupMenuEvent<PopupMenu>& crEvent) override;
    std::vector<std::shared_ptr<MenuItem>> getMenuItems() const override;
    void updateUI() override;
  private:
    void notifyMenuSelected();
    void notifyMenuDeselected();
    void notifyMenuCancelled();
    void buttonClicked() override;

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