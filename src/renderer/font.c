#include "font.h"
#include "rectangle.h"

#define FONT_PNG_WIDTH 208
#define FONT_PNG_HEIGHT 64
#define FONT_SIZE 16

const std::vector<char> chars = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'm', 'n',
                                 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
                                };

/* Function:    Font
   Description: Constructs font data from Png file
   Parameters:  string - Path to font png file
   Returns:     None
*/
Font::Font(std::string pngFilePath) {
  Rect rect;
  uint32_t currPixel = 0;
  uint8_t currLetter = 0;
  uint8_t currLetterHeight = 0;
  uint8_t currHeight = 0;

  std::vector<uint8_t> imgData;
  std::vector<Rect> vertexes(FONT_SIZE);
  struct Png::IHDR ihdr;

  Png png(pngFilePath);
  imgData = png.getImgData();
  ihdr = png.getIhdr();
  uint32_t squarePerWidth = ihdr.width / FONT_SIZE;
  initCharVecSize();
  
  if (png.compareSize(FONT_PNG_WIDTH, FONT_PNG_HEIGHT) == FAIL) {
    std::cout << "Png width and height should be " << FONT_PNG_WIDTH << " x " << FONT_PNG_HEIGHT << std::endl;
    exit(0);
  }

  // If size = 0 then there will be rectangles with area 0 so skip
  for (int i = 0; i < ihdr.width * ihdr.height; i ++) {
    rect = Rect(i % FONT_SIZE, currHeight % FONT_SIZE);
    
    if (ihdr.colorType == Png::ColorType::RGBTRIP)
      rect.setColor(imgData[currPixel], imgData[currPixel + 1], imgData[currPixel + 2]);
    else if(ihdr.colorType == Png::ColorType::RGBTRIPA)
      rect.setColor(imgData[currPixel], imgData[currPixel + 1], imgData[currPixel + 2], imgData[currPixel + 3]);
    
    vertexes[i % FONT_SIZE] = rect;

    if ((i + 1) % FONT_SIZE == 0) {
      insertFontData(currHeight % FONT_SIZE, currLetter, vertexes);
      currLetter ++;
    }

    if (((i + 1) % (ihdr.width * FONT_SIZE)) == 0) {
      currLetterHeight ++;
    }

    if ((i + 1) % ihdr.width == 0) {
      currLetter = (squarePerWidth * currLetterHeight);
      currHeight ++;
    }

    if (ihdr.colorType == Png::ColorType::RGBTRIP)
      currPixel += RGBSIZE;
    else if(ihdr.colorType == Png::ColorType::RGBTRIPA)
      currPixel += RGBASIZE;
  }
}

/* Function:    ~Font
   Description: Class destructor
   Parameters:  None
   Returns:     None
*/
Font::~Font() {
}

/* Function:    operator[]
   Description: Returns the Rect data for a given character in Font
   Parameters:  char - Specific character to grab Rect data
   Returns:     Vector - Rect data to create render data
*/
std::vector<Rect> Font::operator[](const char &rhs) {
  if (fontData.find(rhs) == fontData.end()) {
    std::cout << "Character not found in font" << std::endl;
    exit(0);
  }

  return fontData[rhs];
}

/* Function:    initCharVecSize
   Description: Initializes the vector container size for all characters
   Parameters:  None
   Returns:     None
*/
void Font::initCharVecSize() {
  for (size_t i = 0; i < chars.size(); i ++)
    fontData[chars[i]].resize(FONT_SIZE * FONT_SIZE);
}

/* Function:    insertFontData
   Description: Inserts Rect data into the Char map for a specific character
   Parameters:  uint8_t - Position of current pixel
                uint8_t - The current letter
                Vector  - The Rect data that will be inserted
   Returns:     None
*/
void Font::insertFontData( uint8_t pixelPos, uint8_t currLetter, std::vector<Rect> &data) {
  for (int i = pixelPos * FONT_SIZE; i < (pixelPos + 1) * FONT_SIZE; i ++)
    fontData[chars[currLetter]][i] = data[i % FONT_SIZE];
}