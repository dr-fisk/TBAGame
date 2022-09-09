#ifndef PNG_H
#define PNG_H

#include <string.h>
#include "common.h"

#define IHDR_MASK  0x01
#define IDAT_MASK  0x02
#define IEND_MASK  0x04
#define IDAT_CHAIN 0x08
#define CHUNK_SIZE 16384

#define RGBSIZE 3
#define RGBASIZE 4

enum colorType {
  GRAYSCALE  = 0,
  RGBTRIP  = 2,
  PLTE       = 3,
  GRAYSCALEA = 4,
  RGBTRIPA = 6
};

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

/* Function:    paethRGBBitDepth8
   Description: Paeth Algorightm requires it to be run on each RGB byte
   Parameters:  std::vector<uint8_t> - Structure containing unfiltered img data
                uint32_t - Size of scanline row
                uint8_t  - Number of bytes per pixel
   Returns:     struct RGB - Unfiltered Pixel Color
 */
struct RGB paethRGBBitDepth8(std::vector<uint8_t> imgData, uint32_t scanlineSize, uint8_t rgbSize);

/* Function:    calcPaethByte
   Description: Paeth Algorightm requires it to be run on each RGB byte
   Parameters:  uint8_t - A pixel RGB byte
                uint8_t - B pixel RGB byte
                uint8_t - C pixel RGB byte
   Returns:     uint8_t - Correct predictor pixel
 */
uint8_t calcPaethByte(uint8_t a, uint8_t b, uint8_t c);

/* Function:    rgbBitDepth8
   Description: Iterates through buffer data applying the correct filter on decompressed IDAT chunk data
   Parameters:  std::vector<uint8_t> - Concatenated decompressed IDAT data
                std::vector<uint8_t> - Structure containing unfiltered img data
                struct IHDR - Png information for performing calculations
   Returns:     None
 */
void rgbBitDepth8(std::vector<uint8_t> rgbData, std::vector<uint8_t> &imgData, struct IHDR ihdr);

/* Function:    handlePngColorType
   Description: Handles different colortype PNG configurations
   Parameters:  std::vector<uint8_t> - Concatenated decompressed IDAT data
                std::vector<uint8_t> - Structure containing unfiltered img data
                struct IHDR - Png information for performing calculations
   Returns:     None
 */
void handlePngColorType(std::vector<uint8_t> rgbData, std::vector<uint8_t> &imgData, struct IHDR ihdr);

/* Function:    uncompressIDAT
   Description: Decompresses IDAT chunk data and fills a buffer with the data
   Parameters:  std::vector<uint8_t> - Concatenated uncompressed IDAT data
                std::vector<uint8_t> - Concatenated decompressed IDAT data
   Returns:     None
 */
void uncompressIDAT(std::vector<uint8_t> buffer, std::vector<uint8_t> &decompressedData);

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
                struct IHDR - Png information for performing calculations
   Returns:     std::vector<uint8_t> - Unfiltered IMG data
 */
std::vector<uint8_t> readPng(std::string pngFile, struct IHDR &pihdr);

#endif