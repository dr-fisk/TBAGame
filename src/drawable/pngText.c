#include "drawable/pngText.h"
// Needs bounding later
/* Function:    PngText
   Description: Constructs the render data for a string
   Parameters:  string - String to be rendered to window
                PngFont   - Font tyoe to render text
   Returns:     None
*/
PngText::PngText(const std::string &crText, PngFont &rFont) {
  mRenderData.resize(MESH16_SIZE * crText.size());
  std::vector<Rect> temp(MESH16_SIZE);

  for (int i = 0; i < crText.size(); i ++) {
    temp = rFont[crText[i]];

    for (int j = 0; j < MESH16_SIZE; j ++) {
        updateTextPos(temp[j], j, i);
        mRenderData[(MESH16_SIZE * i) + j] = temp[j].getRenderData()[0];
    }
  }
}

/* Function:    ~PngText
   Description: Class destructor
   Parameters:  None
   Returns:     None
*/
PngText::~PngText() { 
}

/* Function:    getRenderData
   Description: Generates render data to be inserted into a VBO
   Parameters:  None
   Returns:     Vector - Render data
*/
std::vector<RenderData> PngText::getRenderData() {
  return mRenderData;
}

/* Function:    updateTextPos
   Description: Sets the position of each character to be side by side
   Parameters:  Rect - Current Rect to be updated
                uint32_t - meshindex to map out the Rect into a 16x16 grid
                uint32_t - total index to place the characters side by side
   Returns:     None
*/
void PngText::updateTextPos(Rect &rCurrLetter, const uint32_t cMeshIndex, uint32_t cTotalIndex) {
  rCurrLetter.setPos((cMeshIndex % 16) + (16 * cTotalIndex), cMeshIndex / 16);
}