#include <iostream>

#include "pngFont.h"
#include "png.h"
#include "utility/vertexUtility.h"
#include "utility/net_utility.h"

#define FONT_PNG_WIDTH 208
#define FONT_PNG_HEIGHT 64
#define FONT_SIZE 16

const std::vector<char> chars = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'm', 'n',
                                 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
                                };

/* Function:    PngFont
   Description: Constructs font data from Png file
   Parameters:  string - Path to font png file
   Returns:     None
*/
PngFont::PngFont(const std::string &crPngFilePath)
{
  uint32_t currPixel = 0;
  uint8_t currLetter = 0;
  uint8_t currLetterHeight = 0;
  uint8_t currHeight = 0;
  uint8_t modCol = 0;
  uint8_t modHeight = 0;

  std::vector<uint8_t> imgData;
  std::vector<Vertex> vertexes(FONT_SIZE);
  struct Png::IHDR ihdr;
  lg::Color color;
  Vector2<float> pos(0.0f, 0.0f);
  Vector2<uint32_t> size(1, 1);

  Png png(crPngFilePath);
  imgData = png.getImgData();
  ihdr = png.getIhdr();
  uint32_t squarePerWidth = ihdr.width / FONT_SIZE;
  initCharVecSize();
  
  if(png.compareSize(FONT_PNG_WIDTH, FONT_PNG_HEIGHT) == FAIL)
  {
    std::cout << "Png width and height should be " << FONT_PNG_WIDTH << " x " << FONT_PNG_HEIGHT << std::endl;
    exit(-1);
  }

  // If size = 0 then there will be rectangles with area 0 so skip
  for (int i = 0; i < ihdr.width * ihdr.height; i ++)
  {

    if(currLetter >= chars.size())
    {
       std::cout << "Error: Png Font image contains more characters than supported";
    }
    
    if (ihdr.colorType == Png::ColorType::RGBTRIP)
    {
      color = lg::Color(imgData[currPixel], imgData[currPixel + 1], imgData[currPixel + 2]);
    }
    else if(ihdr.colorType == Png::ColorType::RGBTRIPA)
    {
      color = lg::Color(imgData[currPixel], imgData[currPixel + 1], imgData[currPixel + 2], imgData[currPixel + 3]);
    }

    modCol = (i + 1) % FONT_SIZE;
    modHeight = currHeight % FONT_SIZE;

    pos.x = i % FONT_SIZE;
    pos.y = currHeight % FONT_SIZE;

    VertexUtility::createVertex(vertexes[i], pos, size, color);

    // The following if statements keep track of what 16x16 pixel character we are on
    
    // The following keeps track of which Character we are, after 16 columns we are on a new character
    if(modCol == 0)
    {
      insertFontData(modHeight, currLetter, vertexes);
      currLetter ++;
    }

    // This keeps track on which character row we are on, every 16 rows is a new line of characters
    if(((i + 1) % (ihdr.width * FONT_SIZE)) == 0)
    {
      currLetterHeight ++;
    }

    // This keeps track on the row we are on for the image
    if((i + 1) % ihdr.width == 0) {
      currLetter = (squarePerWidth * currLetterHeight);
      currHeight ++;
    }

    if(ihdr.colorType == Png::ColorType::RGBTRIP)
      currPixel += RGBSIZE;
    else if(ihdr.colorType == Png::ColorType::RGBTRIPA)
      currPixel += RGBASIZE;
  }
}

/* Function:    ~PngFont
   Description: Class destructor
   Parameters:  None
   Returns:     None
*/
PngFont::~PngFont()
{
}

/* Function:    operator[]
   Description: Returns the Rect data for a given character in Font
   Parameters:  char - Specific character to grab Rect data
   Returns:     Vector - Rect data to create render data
*/
std::vector<Vertex> PngFont::operator[](const char &crRhs)
{
  if(mFontData.find(crRhs) == mFontData.end())
  {
    std::cout << "Character not found in font" << std::endl;
    exit(-1);
  }

  return mFontData[crRhs];
}

/* Function:    initCharVecSize
   Description: Initializes the vector container size for all characters
   Parameters:  None
   Returns:     None
*/
void PngFont::initCharVecSize()
{
  //FontAttrib temp;
  //memset(&temp, -1, sizeof(FontAttrib));
  for(size_t i = 0; i < chars.size(); i ++)
  {
    mFontData[chars[i]].resize(FONT_SIZE * FONT_SIZE);
    //mFontAttribute[chars[i]] = temp;
  }
}

/* Function:    insertFontData
   Description: Inserts Rect data into the Char map for a specific character
   Parameters:  uint8_t - Position of current pixel
                uint8_t - The current letter
                Vector  - The Rect data that will be inserted
   Returns:     None
*/
void PngFont::insertFontData(const uint8_t cPixelPos, const uint8_t cCurrLetter, const std::vector<Vertex> &crData)
{
  for (int i = cPixelPos * FONT_SIZE; i < (cPixelPos + 1) * FONT_SIZE; i ++)
  {
    mFontData[chars[cCurrLetter]][i] = crData[i % FONT_SIZE];
  }
}