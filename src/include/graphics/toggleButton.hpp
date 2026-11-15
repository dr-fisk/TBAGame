#ifndef TOGGLE_BUTTON_HPP
#define TOGGLE_BUTTON_HPP

#include "graphics/abstractButton.hpp"
#include "graphicsEvent/selectedEvent.hpp"
#include "event/eventDispatcher.hpp"

class ToggleButton : public AbstractButton
{
  public:
    using SelectEvent = SelectedEvent<ToggleButton>;

    //! @brief Default Constructor
    ToggleButton();

    //! @brief Default Destructor
    virtual ~ToggleButton() = default;

    //! @brief Sets the Selected state Texture or animation for the toggle button
    //!
    //! @param[in] cpFrameSource Texture to set
    //!
    //! @return ToggleButton Reference to chain calls
    ToggleButton& setSelectedTexture(const std::shared_ptr<FrameSource> cpFrameSource);

    //! @brief Sets the UnSelected Texture or animation for the toggle button
    //!
    //! @param[in] cpFrameSource Texture to set
    //!
    //! @return ToggleButton Reference to chain calls
    ToggleButton& setUnSelectedTexture(const std::shared_ptr<FrameSource> cpFrameSource);

    //! @brief Sets the selected state of the button
    //!
    //! @param[in] cSelected Selected state
    //!
    //! @return Toggle Button Reference to chain calls
    ToggleButton& setSelected(const bool cSelected);

    //! @brief Adds A Selected Event Subscriber
    //!
    //! @param[in] rListener Selected Event Subscriber
    //!
    //! @return Toggle Button Reference to chain calls
    ToggleButton& addSelectedEventListener(EventSubscriber<SelectEvent>& rListener);
  protected:
    //! Selected flag
    bool mSelected = false;

    //! Selected Event Dispatcher
    EventDispatcher<SelectEvent> mSelectedEventDisp;
  private:
    //! @brief Handles the button clicked logic
    virtual void buttonClicked() override;

    //! @brief Handles Texture swapping
    void setButtonTexture() final;

    //! Selected Texture
    std::shared_ptr<FrameSource> mpButtonSelectedTexture;

    //! Unselected Texture
    std::shared_ptr<FrameSource> mpButtonUnselectedTexture;
};

#endif