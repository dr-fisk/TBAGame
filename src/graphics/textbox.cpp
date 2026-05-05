#include <iostream>

#include "graphics/textbox.hpp"

static char shiftCharConversion(const int cChar)
{
  switch(cChar)
  {
    case 39:
      return '"';
    case 44:
      return '<';
    case 45:
      return '_';
    case 46:
      return '>';
    case 47:
      return '?';
    case 48:
      return ')';
    case 49:
      return '!';
    case 50:
      return '@';
    case 51:
      return '#';
    case 52:
      return '$';
    case 53:
      return '%';
    case 54:
      return '^';
    case 55:
      return '&';
    case 56:
      return '*';
    case 57:
      return ')';
    case 59:
      return ':';
    case 61:
      return '+';
    case 91:
      return '{';
    case 92:
      return '|';
    case 93:
      return '}';
    case 96:
      return '~';
    default:
      return '\0';
  }

  return ';';
}

TextBox::TextBox(const Modifier& crModifier, const TextModifier& crTextModifier, const std::string& crDefaultText)
  : mrModifier(crModifier), mrTextModifier(crTextModifier)
{
  mDefaultText = crDefaultText;
  mpCursor = std::make_shared<Sprite>();
  mpCursor->setColor(lg::White);
  mpCursor->resize({1.0f, static_cast<float>(crTextModifier.getFontSize())});
  mpButton = std::make_shared<Button>(crModifier, crTextModifier);
  mUpdateUI = true;
  mButtonEventSub.setCallback(BIND_EVENT_FN(TextBox::onButtonEvent));
  mFocusSub.setCallback(BIND_EVENT_FN(TextBox::onFocusEvent));
  mpButton->addButtonEventListener(mButtonEventSub);
  mpButton->addFocusEventListener(mFocusSub);
  mCursorIndexPos = 0;
}

TextBox& TextBox::setDefaultText(const std::string& crText)
{
  mDefaultText = crText;
  mUpdateUI = true;
  return *this;
}

void TextBox::dispatchEvent(I_Event<lre::LestRenderEngineEvents>& rEvent)
{
  mpButton->dispatchEvent(rEvent);

  if(mVisible)
  {
    processEvent(rEvent);
  }
}

void TextBox::draw()
{
  if(mUpdateUI)
  {
    updateUI();
  }

  if(mVisible)
  {
    mpButton->draw();

    if(mIsFocused)
    {
      auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mCursorClock);
      if(time.count() >= 500)
      {
        mpCursor->setColor(mpCursor->getColor().getAlpha() == 0 ? lg::White : lg::Transparent);
        mCursorClock = std::chrono::steady_clock::now();
      }
      mpCursor->draw();
    }
  }
}

void TextBox::processEvent(I_Event<lre::LestRenderEngineEvents>& rEvent)
{
  switch(rEvent.GetEventType())
  {
    case lre::LestRenderEngineEvents::KEY_PRESS:
      onKeyPress(static_cast<lre::KeyboardPressEvent&>(rEvent));
    default:
      break;
  }
}

void TextBox::onButtonEvent(AbstractButton::ButtonEvent& rEvent)
{
  switch(rEvent.mAction)
  {
    case GuiEvent::GUI_HOVER:
      break;
    case GuiEvent::GUI_CLICK:
      // std::cout << rEvent.x << ", " << rEvent.y << std::endl;

      if(0 != mInputText.size())
      {
        const Text& text = mpButton->getLabel().getText();
        glm::vec2 prev_pos = text.getCharPos(0);
        // Could update to take into account the size of text later
        // need to account for y pos later too
        mCursorIndexPos = 0;
        for(size_t i = 0; i < mInputText.size(); i ++)
        {
          // std::cout << "Char: " << prev_pos.x << ", " << text.getCharSize(i).x << std::endl;
          if(prev_pos.x < rEvent.x && prev_pos.x + (text.getCharSize(i).x) / 2.0 > rEvent.x)
          {
            mCursorIndexPos = i;
            std::cout << "Selected char: " << mInputText[i] << std::endl;
            break;
          }
          else if(i + 1 >= mInputText.size())
          {
            mCursorIndexPos = i;
          }
        
          prev_pos.x += text.getCharSize(i).x;
        }
      }
      break;
    case GuiEvent::GUI_PRESS:
      break;
    default:
      break;
  }
}

void TextBox::onKeyPress(lre::KeyboardPressEvent& rEvent)
{
  if(!mIsFocused)
  {
    return;
  }

  const char* key = glfwGetKeyName(rEvent.getKey(), rEvent.getScancode());
  if(nullptr != key)
  {
    if(std::isalpha(rEvent.getKey()))
    {
      if(rEvent.getMods() & GLFW_MOD_CAPS_LOCK || rEvent.getMods() & GLFW_MOD_SHIFT)
      {
        mInputText.insert(mCursorIndexPos, 1, std::toupper(*key));
      }
      else
      {
        mInputText.insert(mCursorIndexPos, 1, *key);
      }
      mCursorIndexPos ++;
    }
    else
    {
      if(rEvent.getMods() & GLFW_MOD_SHIFT)
      {
        mInputText.insert(mCursorIndexPos, 1, shiftCharConversion(static_cast<int>(*key)));
      }
      else
      {
        mInputText.insert(mCursorIndexPos, 1, *key);
      }
      mCursorIndexPos ++;
    }
  }
  else
  {
    switch(rEvent.getKey())
    {
      case GLFW_KEY_BACKSPACE:
        if(0 != mInputText.size() && mCursorIndexPos > 0)
        {
          mInputText.erase(mInputText.begin() + mCursorIndexPos - 1);
          mCursorIndexPos --;
        }
        else
        {
          return;
        }
        break;
      case GLFW_KEY_DELETE:
        if(0 != mInputText.size() && mCursorIndexPos < mInputText.size())
        {
          mInputText.erase(mInputText.begin() + mCursorIndexPos);
        }
        else
        {
          return;
        }
        break;
      case GLFW_KEY_TAB:
        mInputText.insert(mCursorIndexPos, 1, '\t');
        mCursorIndexPos ++;
        break;
      case GLFW_KEY_ENTER:
        if(rEvent.getMods() & GLFW_MOD_SHIFT)
        {
          mInputText.insert(mCursorIndexPos, 1, '\n');
          mCursorIndexPos ++;
        }
        else
        {
          SubmitEvent<Component> event(this, mInputText);
          mSubmitEventDispatcher.notify(event);
        }
        break;
      case GLFW_KEY_LEFT:
        if(0 != mCursorIndexPos)
        {
          mCursorIndexPos --;
        }
        break;
      case GLFW_KEY_RIGHT:
        if(mInputText.size() != mCursorIndexPos)
        {
          mCursorIndexPos++;
        }
        break;
      case GLFW_KEY_SPACE:
        mCursorIndexPos++;
        mInputText += " ";
        break;
      default:
        break;
    }
  }

  mUpdateUI = true;
}

void TextBox::updateUI()
{
  auto& label = mpButton->getLabel();
  if(0 == mInputText.size())
  {
    label.setString(mDefaultText);
    mCursorIndexPos = 0;
  }
  else
  {
    // glm::vec2 size = mrTextModifier.getFont().getCharacterDimensions(mrTextModifier.getFontSize(), mInputText.back());
    // if()
    // {
      label.setString(mInputText);
    // }
  }

  label.updateUI();

  if(!mInputText.empty() && mCursorIndexPos > 0)
  {
    glm::vec2 pos = label.getText().getCharPos(mCursorIndexPos - 1);
    glm::vec2 size = label.getText().getCharSize(mCursorIndexPos - 1);
    mpCursor->setPos({pos.x + size.x + mpCursor->getSize().x / 2.0f, pos.y + size.y / 2.0f });
  }
  else if(!mDefaultText.empty())
  {
    mpCursor->setPos({label.getText().getCharPos(0).x - mpCursor->getSize().x / 2.0f, label.getText().getCharPos(0).y + label.getText().getCharSize(0).y / 2.0f});
  }

  mUpdateUI = false;
}

void TextBox::onFocusEvent(FocusEvent<Component>& rFocusEvent)
{
  setFocus(rFocusEvent.mFocus);
  mCursorClock = std::chrono::steady_clock::now();
  mpCursor->setColor(lg::White);
}