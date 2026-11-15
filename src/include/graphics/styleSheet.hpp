#ifndef STYLE_SHEET
#define STYLE_SHEET

#include <cstdint>

//! @brief Container to style textures by defining visual indicators that are separate from quad bounds 
class StyleSheet
{
  public:
    //! Visual Top Coordinate
    uint32_t mVisualTop = 0;
    
    //! Visual Left Coordinate
    uint32_t mVisualLeft = 0;
    
    //! Visual Width
    uint32_t mVisualWidth = 0;
    
    //! Visual Height
    uint32_t mVisualHeight = 0;
};

#endif