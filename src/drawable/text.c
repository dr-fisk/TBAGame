#include "text.h"
// Needs bounding later
/* Function:    Text
   Description: Constructs the render data for a string
   Parameters:  string - String to be rendered to window
                Font   - Font tyoe to render text
   Returns:     None
*/
Text::Text(std::string text, Font &font) {
  renderData.resize(MESH16_SIZE * text.size());
  std::vector<Rect> temp(MESH16_SIZE);

  for (int i = 0; i < text.size(); i ++) {
    temp = font[text[i]];

    for (int j = 0; j < MESH16_SIZE; j ++) {
        updateTextPos(temp[j], j, i);
        renderData[(MESH16_SIZE * i) + j] = temp[j].createRenderData();
    }
  }
}

/* Function:    ~Text
   Description: Class destructor
   Parameters:  None
   Returns:     None
*/
Text::~Text() { 
}

/* Function:    getRenderData
   Description: Generates render data to be inserted into a VBO
   Parameters:  None
   Returns:     Vector - Render data
*/
std::vector<RenderData> Text::getRenderData() {
  return renderData;
}

/* Function:    updateTextPos
   Description: Sets the position of each character to be side by side
   Parameters:  Rect - Current Rect to be updated
                uint32_t - meshindex to map out the Rect into a 16x16 grid
                uint32_t - total index to place the characters side by side
   Returns:     None
*/
void Text::updateTextPos(Rect &currLetter, uint32_t meshIndex, uint32_t totalIndex) {
  currLetter.setPos((meshIndex % 16) + (16 * totalIndex), meshIndex / 16);
}