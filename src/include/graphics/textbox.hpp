#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "graphics/button.hpp"
#include "graphics/label.hpp"
#include "event/event.hpp"
#include "event/eventSubscriber.hpp"
#include "input/keyboardEvent.hpp"

class TextBox : public Component
{
public:

  //! @brief Textbox Constructor
  //!
  //! @param[in] crPos Postion of the TextBox
  //! @param[in] crSize Size of the TextBox
  //! @param[in] crDefaultText Default Text to set to label
  //! @param[in] crColor Textbox color (TODO determine if wanted)
  TextBox(const glm::vec2& crPos, const glm::vec2& crSize, const std::string& crDefaultText,
    const lg::Color& crColor=lg::White);
  
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
private:
  enum TextBoxState
  {
    UNFOCUSED_STATE,
    FOCUSED_STATE
  };

  // std::shared_ptr<Texture2D> mMouseTexture;
  std::string mDefaultText;
  TextBoxState mState;
  std::shared_ptr<Sprite> mBox;
  EventSubscriber<LestRenderEngine::KeyboardPressEvent> mKeyPressSub;
};

#endif