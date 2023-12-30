#include "drawable/pngText.h"
#include "utility/net_utility.h"
#include "utility/vertexUtility.h"

const uint16_t MESH16_SIZE = 256;

// Needs bounding later
/* Function:    PngText
   Description: Constructs the render data for a string
   Parameters:  string - String to be rendered to window
                PngFont   - Font tyoe to render text
   Returns:     None
*/
PngText::PngText(const std::string& crText, PngFont& rFont)
{
  mVertex.resize(MESH16_SIZE * crText.size());
  std::vector<Vertex> temp(MESH16_SIZE);
  Vector2<float> pos(0.0f, 0.0f);
  Vector2<uint32_t> size(16, 16);

  for (int i = 0; i < crText.size(); i ++)
  {
    temp = rFont[crText[i]];

    for (int j = 0; j < MESH16_SIZE; j ++)
    {
        pos.x = (j % 16) + (16 * i);
        pos.y = j / 16;
        VertexUtility::createVertex(mVertex[(MESH16_SIZE * i) + j], pos, size, temp[j].rgba1);
    }
  }
}

/* Function:    ~PngText
   Description: Class destructor
   Parameters:  None
   Returns:     None
*/
PngText::~PngText()
{ 
}

/* Function:    getVertex
   Description: Generates render data to be inserted into a VBO
   Parameters:  None
   Returns:     Vector - Render data
*/
std::vector<Vertex> PngText::getVertex()
{
  return mVertex;
}

/* Function:    updateTextPos
   Description: Sets the position of each character to be side by side
   Parameters:  Rect - Current Rect to be updated
                uint32_t - meshindex to map out the Rect into a 16x16 grid
                uint32_t - total index to place the characters side by side
   Returns:     None
*/
void PngText::updateTextPos(Rect& rCurrLetter, const uint32_t cMeshIndex, uint32_t cTotalIndex)
{
  rCurrLetter.setPos((cMeshIndex % 16) + (16 * cTotalIndex), cMeshIndex / 16);
}