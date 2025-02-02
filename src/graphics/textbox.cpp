#include <iostream>

#include "graphics/textbox.hpp"

TextBox::TextBox(const glm::vec2& crPos, const glm::vec2& crSize, const std::string& crDefaultText,
  const lg::Color& crColor)
{
  glm::vec2 tempPos(0, 0);
  mBox = std::make_shared<Sprite>(crPos, crSize, lg::Grey);
  // mDefaultText = std::make_unique<Text>(nullptr, crDefaultText, prResourceMngr, 12, tempPos);
  // mState = DEFAULT_STATE;
  setPos(crPos);
}

TextBox& TextBox::setDefaultText(const std::string& crText)
{
  mDefaultText = crText;
  mUpdateUI = true;
  return *this;
}

void TextBox::update(const Event& crEvent)
{
  // if(mpButton->clicked(crEvent))
  // {
  //   std::cout << "Clicked" << std::endl;
  //   // Grab index location where clicked
  //   mState = FOCUSED_STATE;
  // }



  switch(crEvent.Type)
  {
    case Event::EventType::KeyPress:
      // mInputText.addText();
      break;
  }
}

void TextBox::draw()
{
  if(0 < mInputText->getNumChars() /* Maybe add a flag if default text should be used*/)
  {
    //draw default text
  }
  else
  {
    //draw input text
  }
}

void TextBox::movePos(const glm::vec2& crMoveVector)
{
  mDefaultText->movePos(crMoveVector);
  mInputText->movePos(crMoveVector);
}

void TextBox::setPos(const glm::vec2& crPos)
{


}

void TextBox::updateTextPos()
{
  glm::vec2 textSize = mDefaultText->getSize();
  glm::vec2 buttonCenter = mBox->getPos();
  // Maybe for this one make a changeable left and top position
  mDefaultText->setPos({buttonCenter.x - (textSize.x / 2.0f), buttonCenter.y - (textSize.y / 2.0f)});
  mInputText->setPos({buttonCenter.x - (textSize.x / 2.0f), buttonCenter.y - (textSize.y / 2.0f)});
}
