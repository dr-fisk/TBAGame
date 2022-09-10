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

class Png {
public:
enum ColorType {
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

Png(std::string pngFile);
~Png();
std::vector<uint8_t> getImgData();
struct IHDR getIhdr();

private:
  void readPng();
  void parseIHDR(uint32_t chunkLength);
  struct RGB subPixelRGB(struct RGB pixel1, struct RGB pixel2);
  struct RGB addPixelRGB(struct RGB pixel1, struct RGB pixel2);
  struct RGB paethRGBBitDepth8(uint32_t scanlineSize, uint8_t rgbSize);
  uint8_t calcPaethByte(uint8_t a, uint8_t b, uint8_t c);
  void rgbBitDepth8(std::vector<uint8_t> rgbData);
  void handlePngColorType(std::vector<uint8_t> rgbData);
  void uncompressIDAT(std::vector<uint8_t> buffer, std::vector<uint8_t> &decompressedData);
  void parseICCP(uint32_t chunkLength);
  
  struct IHDR ihdr;
  std::vector<uint8_t> imgData;
  std::ifstream pngFile;
};

#endif