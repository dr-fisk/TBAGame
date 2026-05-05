#ifndef FRAME_HPP
#define FRAME_HPP

#include "component.hpp"

class Frame : public Component
{
  public:
    //! @brief Default Constructor
    Frame();

    //! @brief Default Destructor
    ~Frame() = default;

    //! @brief Draws the Frame
    //!
    //! @return None
    void draw() override;

    //! @brief Adds component to Frame
    //!
    //! @param[in] pComponent Component Pointer
    //!
    //! @return Frame Reference
    Frame& addComponent(std::shared_ptr<Component> pComponent) override;

    void updateUI(){}

  private:
    //! @brief MouseButtonPressEvent Handler
    //!
    //! @param rMouseButtonPressEvent MouseButtonPressEvent
    //!
    //! @return None 
    void onMousePress(lre::MouseButtonPressEvent& rMouseButtonPressEvent);

    //! @brief MouseButtonReleaseEvent Handler
    //!
    //! @param rMouseButtonReleaseEvent MouseButtonReleaseEvent
    //!
    //! @return None 
    void onMouseRelease(lre::MouseButtonReleaseEvent& rMouseButtonReleaseEvent);

    //! @brief MouseMoveEvent Handler
    //!
    //! @param rMouseMoveEvent MouseMoveEvent
    //!
    //! @return None 
    void onMouseMove(lre::MouseMoveEvent& rMouseMoveEvent);

    //! @brief KeyboardPressEvent Handler
    //!
    //! @param rKeyboardPressEvent KeyboardPressEvent
    //!
    //! @return None 
    void onKeyPress(lre::KeyboardPressEvent& rKeyboardPressEvent);

    //! @brief KeyboardReleaseEvent Handler
    //!
    //! @param rKeyboardReleaseEvent KeyboardReleaseEvent
    //!
    //! @return None 
    void onKeyRelease(lre::KeyboardReleaseEvent& rKeyboardReleaseEvent);

    Component::MousePressListener mEDTMousePressListener;
    Component::MouseReleaseListener mEDTMouseReleaseListener;
    Component::MouseMoveListener mEDTMouseMoveListener;
    Component::KeyPressListener mEDTKeyPressListener;
    Component::KeyReleaseListener mEDTKeyReleaseListener;
};

#endif