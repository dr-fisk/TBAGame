#ifndef PNG_H
#define PNG_H

#include <string.h>
#include "common.h"

#define IHDR_MASK  0x01
#define IDAT_MASK  0x02
#define IEND_MASK  0x04
#define IDAT_CHAIN 0x08
#define CHUNK_SIZE 16384

struct IHDR {
  uint32_t width;
  uint32_t height;
  uint8_t  bitDepth;
  uint8_t  colorType;
  uint8_t  compressionMethod;
  uint8_t  filterMethod;
  uint8_t  interfaceMethod;
};

struct RGB {
  uint8_t Red;
  uint8_t Green;
  uint8_t Blue;
};

struct RGBA {
  uint16_t Red;
  uint16_t Green;
  uint16_t Blue;
  uint8_t  Alpha;
};

enum FilterMethods {NONE, SUB, UP, AVERAGE, PAETH};

/* Function:    parseIHDR
   Description: Parses IHDR from png file
   Parameters:  ifstream - file descriptor for file we are reading
                uint32_t - The amount of bytes to read
                struct IHDR - IHDR struct to store values from parsed IHDR
   Returns:     None
 */
void parseIHDR(std::ifstream &in, uint32_t chunkLength, struct IHDR *ihdr);

/* Function:    subPixelRGB
   Description: subtracts the RGB vals from two Pixels
   Parameters:  struct RGB - Pixel 1 RGB values
                struct RGB - Pixel 2 RGB values
   Returns:     struct RGB - New pixel RGB values
 */
struct RGB subPixelRGB(struct RGB pixel1, struct RGB pixel2);

/* Function:    addPixelRGB
   Description: Adds the RGB vals from two Pixels
   Parameters:  struct RGB - Pixel 1 RGB values
                struct RGB - Pixel 2 RGB values
   Returns:     struct RGB - New pixel RGB values
 */
struct RGB addPixelRGB(struct RGB pixel1, struct RGB pixel2);

/* Function:    paethColorType6BitDepth8
   Description: Paeth Algorightm requires it to be run on each RGB byte
   Parameters:  uint16_t - A pixel RGB byte
                uint16_t - B pixel RGB byte
                uint16_t - C pixel RGB byte
   Returns:     uint16_t - Correct predictor pixel
 */
struct RGB paethColorType6BitDepth8(uint16_t a, uint16_t b, uint16_t c);

/* Function:    paethColorType2BitDepth8
   Description: Paeth Algorightm requires it to be run on each RGB byte
   Parameters:  uint8_t - A pixel RGB byte
                uint8_t - B pixel RGB byte
                uint8_t - C pixel RGB byte
   Returns:     uint8_t - Correct predictor pixel
 */
struct RGB paethColorType2BitDepth8(std::vector<uint8_t> imgData, uint32_t scanlineSize);

/* Function:    calcPaeth
   Description: Applies the Paeth Algorithm to the current row of pixels
   Parameters:  uint8t * - Buffer data containing decompressed png IDAT chunk values
                uint32_t - The end of the a row of pixels in the buffer
                int32_t  - Current index in the buffer data
   Returns:     struct RGB - RGB values to be used to filter pixel at index
 */
struct RGB calcPaeth(uint8_t *rgbVals, uint32_t width, int32_t index);

/* Function:    colorType2BitDepth8
   Description: Iterates through buffer data applying the correct filter on decompressed IDAT chunk data
   Parameters:  uint8t * - Buffer data containing decompressed png IDAT chunk values
                uint32_t - The amount of bytes existing in rgbVals
                IHDR     - ihdr properties
   Returns:     None
 */
void colorType2BitDepth8(uint8_t *rgbVals, std::vector<uint8_t> &imgData, uint32_t bytes, struct IHDR ihdr, uint32_t &bytesRead);

/* Function:    uncompressIDAT
   Description: Decompresses IDAT chunk data and fills a buffer with the data
   Parameters:  ifstream - File descriptor to read data from
                vector<uint8_t> - Compressed IDAT chunk data
                IHDR - ihdr properties
   Returns:     None
 */
void uncompressIDAT(std::ifstream &in, std::vector<uint8_t> buffer, std::vector<uint8_t> &finalImgData, struct IHDR ihdr);

/* Function:    parseICCP
   Description: Parses ICCP chunk, but currently doesn't do that, just used to parse items
                that are not IHDR and IDAT from png
   Parameters:  ifstream - File descriptor to read data from
                uint32_t - Amount of bytes to read
   Returns:     None
 */
void parseICCP(std::ifstream &in, uint32_t chunkLength);

/* Function:    readPng
   Description: Parses an entire png file and stores rgb values to recreate img
   Parameters:  string - Location of file to read data from
   Returns:     None
 */
std::vector<uint8_t> readPng(std::string pngFile, uint32_t &width, uint32_t &height);

#endif