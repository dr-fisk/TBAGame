#include "drawable/mesh.h"
#include "png.h"
#include "drawable/rectangle.h"

/* Function:    Mesh
   Description: Default constructor
   Parameters:  None
   Returns:     None
 */
Mesh::Mesh() : Drawable() {
}

/* Function:    Mesh
   Description: Initializes mesh texture
   Parameters:  std::string - Path to PNG file
                uint8_t - Left coordinate for Rect
                uint8_t - Top coordinate for Rect
                uint8_t - Multiplier for size of pixel
   Returns:     None
 */
Mesh::Mesh(const std::string &crPngFile, const uint8_t cLeft, const uint8_t cTop, const uint8_t cSize)
{
  Rect rect;
  uint32_t l = 0;
  uint32_t t = 0;
  uint32_t currPixel  = 0;
  std::vector<uint8_t> imgData;
  struct Png::IHDR ihdr;
  Png png(crPngFile);
  imgData = png.getImgData();
  ihdr = png.getIhdr();

  mMesh.resize(ihdr.width * ihdr.height);
  // If size = 0 then there will be rectangles with area 0 so skip
  for (int i = 0; i < ihdr.width * ihdr.height && cSize > 0; i ++) {
    t = ((i / ihdr.width) + cTop) * cSize;
    l = ((i % ihdr.width) + cLeft) * cSize;

    rect = Rect(l, t, cSize, cSize);
    // handle diff colortypes still
    if (ihdr.colorType == Png::ColorType::RGBTRIP)
      rect.setColor(imgData[currPixel], imgData[currPixel + 1], imgData[currPixel + 2]);
    else if(ihdr.colorType == Png::ColorType::RGBTRIPA)
      rect.setColor(imgData[currPixel], imgData[currPixel + 1], imgData[currPixel + 2], imgData[currPixel + 3]);

    mMesh[i] = rect.createVertex();

    if (ihdr.colorType == Png::ColorType::RGBTRIP)
      currPixel += RGBSIZE;
    else if(ihdr.colorType == Png::ColorType::RGBTRIPA)
      currPixel += RGBASIZE;
  }

  imgData.clear();
}

/* Function:    getVertex
   Description: Getter for render data coressponding to mesh object
   Parameters:  None
   Returns:     std::vector<Vertex> Mesh data
 */
std::vector<Vertex> Mesh::getVertex()
{
  return mMesh;
}

/* Function:   ~Mesh
   Description: Destroys mesh object
   Parameters:  None
   Returns:     None
 */
Mesh::~Mesh()
{

}