#ifndef POPUP_MENU_HPP
#define POPUP_MENU_HPP

#include <vector>
#include <memory>

#include "graphics/component.hpp"
#include "graphics/menuItem.hpp"
#include "shapes/box2D.hpp"
#include "graphics/popupMenuListener.hpp"

class PopupMenu : public Component, public PopupMenuListener<PopupMenu>
{
  public:
    PopupMenu();
    ~PopupMenu() = default;
    void addItem(const std::shared_ptr<MenuItem> cpMenuItem);
    void draw() override;
    PopupMenu& setPreferredSize(const float cWidth, const float cHeight);
    void handleEvent(const Event& crEvent);
    void setMenuLocation(const glm::vec2& crPos);
    void setInvoker(const AbstractButton* cpInvoker);
    void addPopupMenuListerner(PopupMenuListener<PopupMenu>* cpListener);

    void popupMenuCancelled(const PopupMenuEvent<PopupMenu>& crEvent) override;
    void popupMenuWillBecomeInvisible(const PopupMenuEvent<PopupMenu>& crEvent) override;
    void popupMenuWillBecomeVisible(const PopupMenuEvent<PopupMenu>& crEvent) override;
    void setVisible(const bool cVisible) override;
    std::vector<std::shared_ptr<MenuItem>> getMenuItems() const;
    void updateUI() override;
  private:
    void updatePopupMenuItemPositions();
    void notifyCancelled();
    void notifyInvisible();
    void notifyVisible();
    void checkMousePressOutOfBounds(const Event& crEvent);
    void popupMenuCancelled();

    std::vector<std::shared_ptr<MenuItem>> mComponents;
    std::vector<PopupMenuListener<PopupMenu>*> mPopupMenuListeners;
    Box2D<float> mBounds;
    glm::vec2 mPreferredSize;
    const AbstractButton* cmpInvoker;
    PopupMenu* mActiveSubMenu;
};

#endif