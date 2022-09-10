#include "mesh.h"
#include "png.h"

/* Function:    Mesh
   Description: Default constructor
   Parameters:  None
   Returns:     None
 */
Mesh::Mesh() {
}

/* Function:    Mesh
   Description: Initializes mesh texture
   Parameters:  GLfloat - Window width
                GLfloat - Window height
                std::string - Path to PNG file
                uint8_t - Left coordinate for Rect
                uint8_t - Top coordinate for Rect
                uint8_t - Multiplier for size of pixel
   Returns:     None
 */
Mesh::Mesh(GLfloat wWidth, GLfloat wHeight, std::string pngFile, uint8_t left, uint8_t top, uint8_t size) {
  Rect rect;
  uint32_t l = 0;
  uint32_t t = 0;
  uint32_t currPixel = 0;
  std::vector<uint8_t> imgData;
  struct Png::IHDR ihdr;
  Png png(pngFile);
  imgData = png.getImgData();
  ihdr = png.getIhdr();

  // If size = 0 then there will be rectangles with area 0 so skip
  for (int i = 0; i < ihdr.width * ihdr.height && size > 0; i ++) {
    t = ((i / ihdr.height) + top) * size;
    l = ((i % ihdr.width) + left) * size;

    rect = Rect(l, t, size, size);
    // handle diff colortypes still
    if (ihdr.colorType == Png::ColorType::RGBTRIP)
      rect.setColor(imgData[currPixel], imgData[currPixel + 1], imgData[currPixel + 2]);
    else
       rect.setColor(imgData[currPixel], imgData[currPixel + 1], imgData[currPixel + 2], imgData[currPixel + 3]);

    mesh.push_back(rect.createRectVertexData(wWidth, wHeight));

    if (ihdr.colorType == Png::ColorType::RGBTRIP)
      currPixel += RGBSIZE;
    else
       currPixel += RGBASIZE;
  }

  imgData.clear();
}

/* Function:    getMeshData
   Description: Getter for mesh data
   Parameters:  None
   Returns:     std::vector<RectVetexData> Mesh data
 */
std::vector<RectVertexData>& Mesh::getMeshData() {
  return mesh;
}

/* Function:   ~Mesh
   Description: Destroys mesh object
   Parameters:  None
   Returns:     None
 */
Mesh::~Mesh() {

}