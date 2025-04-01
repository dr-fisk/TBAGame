#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "graphics/button.hpp"
#include "graphics/label.hpp"
#include "event/event.hpp"
#include "event/eventSubscriber.hpp"

class TextBox : public Component
{
public:

  //! @brief Textbox Constructor
  //!
  //! @param[in] crModifier
  //! @param[in] crTextModifier
  //! @param[in] crDefaultText Default Text to set to label
  TextBox(const Modifier& crModifier, const TextModifier& crTextModifier, const std::string& crDefaultText);
  
  //! @brief Delete Default Constructor
  TextBox() = delete;

  //! @brief Default Destructor
  ~TextBox() = default;

  //! @brief Draws the Textbox
  //!
  //! @return None
  void draw();
  // void movePos(const glm::vec2& crMoveVector);
  // void setPos(const glm::vec2& crPos);
  // void setFont(const std::shared_ptr<Font>& crFont);

  //! @brief Sets the Default Text that will be displayed when there is no text input from the user
  //!
  //! @param[in] crText Default Text to set
  //!
  //! @return Textbox reference to chain calls 
  TextBox& setDefaultText(const std::string& crText);

  void dispatchEvent(I_Event<lre::LestRenderEngineEvents>& rEvent) override;

  void onButtonEvent(AbstractButton::ButtonEvent& rEvent);

  void updateUI() override;
private:
  void processEvent(I_Event<lre::LestRenderEngineEvents>& rEvent) override;

  void onKeyPress(lre::KeyboardPressEvent& rEvent);

  enum TextBoxState
  {
    UNFOCUSED_STATE,
    FOCUSED_STATE
  };

  // std::shared_ptr<Texture2D> mMouseTexture;
  std::string mDefaultText;
  std::string mInputText;
  int mCursorIndexPos;
  TextBoxState mState;
  std::shared_ptr<Sprite> mBox;
  std::shared_ptr<Button> mpButton;
  EventSubscriber<AbstractButton::ButtonEvent> mButtonEventSub;
};

#endif