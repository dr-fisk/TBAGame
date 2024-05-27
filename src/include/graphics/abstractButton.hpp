#ifndef ABSTRACT_BUTTON_HPP
#define ABSTRACT_BUTTON_HPP

#include <functional>
#include <list>

#include "graphics/label.hpp"
#include "event/event.hpp"
#include "graphics/itemListener.hpp"
#include "graphics/actionListener.hpp"

class AbstractButton : public Component
{
  public:
    AbstractButton();
    virtual ~AbstractButton() = default;
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Setters
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    AbstractButton& setText(const Text& crText);
    AbstractButton& setTextColor(const lg::Color& crColor);
    AbstractButton& setHorizontalAlignment(const Label::HorizontalAlign cAlign);
    AbstractButton& setVerticalAlignment(const Label::VerticalAlign cAlign);
    AbstractButton& setTextPos(const glm::vec2& crPos);
    AbstractButton& setDefaultTexture(const std::shared_ptr<Texture2D>& crpTexture);
    AbstractButton& setHoverTexture(const std::shared_ptr<Texture2D>& crpTexture);
    AbstractButton& setPressedTexture(const std::shared_ptr<Texture2D>& crpTexture);
    AbstractButton& setDefaultColor(const lg::Color& crColor);
    AbstractButton& setHoverColor(const lg::Color& crColor);
    AbstractButton& setPressedColor(const lg::Color& crColor);
    virtual AbstractButton& movePos(const glm::vec2& crMove) override;
    virtual AbstractButton& setPos(const glm::vec2& crPos)  override;
    virtual AbstractButton& resize(const glm::vec2& crSize) override;
    AbstractButton& setString(const std::string& crString);
    AbstractButton& setPadding(const glm::vec2& crPadding);
    AbstractButton& addItemListener(ItemListener* cpItemListener);
    AbstractButton& addActionListener(ActionListener<AbstractButton>* cpActionListener);
    void removeActionListener(const ActionListener<AbstractButton>* cpActionListener);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getters
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::string getString() const;
    glm::vec2 getPos() const;
    glm::vec2 getSize() const;
    bool isPressed() const;
    bool isHover() const;
    bool isDefault() const;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Event Handlers
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void handleEvent(const Event& crEvent);
    virtual void draw() override;
    void onClick(std::function<void()> pFunc);
    bool wasClicked() const;
  protected:
    void mouseMoveUpdate(const Event::MouseMoveEvent& crEvent);
    void mouseButtonUpdate(const Event::MouseButtonEvent& crEvent);
    void mouseButtonRelease(const Event::MouseButtonEvent& crEvent);
    bool isInAABB(const glm::vec2& crPos);
    bool isInAABB(const glm::vec2& crPos, const glm::vec2& crPadding);
    void setButtonTexture();
    virtual void buttonClicked() = 0;

    enum ButtonState
    {
      DEFAULT_STATE,
      HOVER_STATE,
      PRESSED_STATE
    };

    Label mLabel;
    std::shared_ptr<Texture2D> mpDefaultTexture;
    std::shared_ptr<Texture2D> mpHoverTexture;
    std::shared_ptr<Texture2D> mpPressedTexture;
    lg::Color mDefaultColor;
    lg::Color mHoverColor;
    lg::Color mPressedColor;
    ButtonState mState;
    glm::vec2 mPressedPadding;
    std::list<ItemListener*> mItemListeners;
    std::list<ActionListener<AbstractButton>*> mActionListeners;
    std::function<void()> mCallback;
    bool mClicked;
};

#endif