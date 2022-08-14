#include <string.h>
#include "common.h"

#define IHDR_MASK  0x01
#define IDAT_MASK  0x02
#define IEND_MASK  0x04
#define IDAT_CHAIN 0x08
#define CHUNK_SIZE 16384

enum FilterMethods {NONE, SUB, UP, AVERAGE, PAETH};
const std::vector<uint8_t> png = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, '\0'};

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

/* There is no endian issues for 1 byte values which is why only width and height needs to be rearranged */
void parseIHDR(std::ifstream &in, uint32_t chunkLength, struct IHDR *ihdr) {
  in.read((char *) ihdr, chunkLength);
  ihdr->width = htonl(ihdr->width);
  ihdr->height = htonl(ihdr->height);

  if ((ihdr->width == 0) || (ihdr->height == 0)) {
    std::cout << "Error! Invalid image dimensions." << std::endl;
    exit(0);
  }
}

struct RGB subPixelRGB(struct RGB pixel1, struct RGB pixel2) {
  return {(uint8_t)((pixel1.Red - pixel2.Red)), (uint8_t)((pixel1.Green - pixel2.Green)),
          (uint8_t)((pixel1.Blue - pixel2.Blue))};
}

struct RGB addPixelRGB(struct RGB pixel1, struct RGB pixel2) {
  return {(uint8_t)((pixel1.Red + pixel2.Red)), (uint8_t)((pixel1.Green + pixel2.Green)),
          (uint8_t)((pixel1.Blue + pixel2.Blue))};
}

struct RGB absPixelRGB(struct RGB pixel) {
  return {(uint8_t)abs(pixel.Red), (uint8_t)abs(pixel.Green), (uint8_t)abs(pixel.Blue)};
}

bool lessThanEqualPix(struct RGB pixel1, struct RGB pixel2) {
  return (pixel1.Red <= pixel2.Red) && (pixel1.Green <= pixel2.Green) && (pixel1.Blue <= pixel2.Blue);
}

int32_t convertRGBToInt(struct RGB pixel) {
  int32_t rgb = 0;
  int32_t temp = 0;

  rgb = pixel.Red;
  rgb = rgb << 16;
  temp = pixel.Green;
  temp = temp << 8;
  rgb += temp;
  rgb += pixel.Blue;

  return rgb;
}

/*
  Calculates the PAETH algorithm.
  The PAETH algorithm works on bytes, which means that one byte values will not work.
  For example you need to add two rgb values and compare that with another value.
  Assume 1 byte values 255 and 1. 255 + 1 overflows a uint8_t and results in 0.
  The above would mean that 255 + 1 <= 255 which is wrong in the paeth algorithm.
  
  To Overcome this I converted the rgbs into an integer as 0x0000RRRRGGGGBBBB
  This allows us to add integers without worrying about overflows.
*/
struct RGB calcPaeth(uint8_t *rgbVals, uint32_t width, int32_t index) {
  struct RGB a, b, c, pr;
  int32_t iA, iB, iC, p, pa, pb, pc;
  iA = 0;
  iB = 0;
  iC = 0;

  /* The below blocks gathers the pixel RGB to the left of the current index, the Pixel RGB to the upper left of the current index,
     and the Pixel RGB above the current index
  */
  a.Red   = (index - 1) % width != 0 ? rgbVals[index - 3] : 0;
  a.Green = (index - 1) % width != 0 ? rgbVals[index - 2] : 0;
  a.Blue  = (index - 1) % width != 0 ? rgbVals[index - 1] : 0;

  b.Red   = (index - 49) > 0 ? rgbVals[index - 49] : 0;
  b.Green = (index - 49) > 0 ? rgbVals[index + 1 - 49] : 0;
  b.Blue  = (index - 49) > 0 ? rgbVals[index + 2 - 49] : 0;

  c.Red   = (index - 52) > 0 ? rgbVals[index - 52] : 0;
  c.Green = (index - 52) > 0 ? rgbVals[index + 1 - 52] : 0;
  c.Blue  = (index - 52) > 0 ? rgbVals[index + 2 - 52] : 0;

  iA = convertRGBToInt(a);
  iB = convertRGBToInt(b);
  iC = convertRGBToInt(c);

  p = iA + iB - iC;
  pa = abs(p - iA);
  pb = abs(p - iB);
  pc = abs(p - iC);

  if (pa <= pb && pa <= pc) {
    pr = a;
  }
  else if (pb <= pc) {
    pr = b;
  }
  else {
    pr = c;
  }

  return pr;
}

/*
  index i will always be either the filter method or a pixel starting on the Red color value_comp
  index i will never be Blue nor Green, to extract the blue and green for the current pixel do i + 1 for Green and i + 2 for red
  
  Here is an example below:
  We have a uint8_t array with 1 byte values represented as F (filter method), R (Red color value), G (Green Color Value), B (Blue Color Value)
  If our index i lands on F, we will add 1 to our index and that will put our index on R. Each time our index i is on R we will add 3 to our index i.
  We add 3 because each pixel contains an RGB value, so adding 3 to our index i essentially puts us on the next pixel
  
  F RGB RGB RGB RGB
  F RGB RGB RGB RGB
  F RGB RGB RGB RGB
  Filter UP adds the pixel RGB to the current pixel RGB 
*/
void applyFilterMethod(uint8_t *rgbVals, uint32_t width, uint32_t height) {
  struct RGB filterPix;
  uint8_t filterValue = 0;
  uint32_t decompressedWidth = (width * 3) + 1;

 for (int i = 0; i < (width * height) * 3 + width;) {
    if (i % decompressedWidth == 0) {
      filterValue = rgbVals[i];
      i += 1;
    }
    else {
      switch(filterValue) {
        case NONE:
          // No filter do nothing but set filter pixels as to avoid any junk memory
          filterPix.Red   = 0;
          filterPix.Green = 0;
          filterPix.Blue  = 0;
          break;
        case SUB:
          filterPix.Red   = (i - 1) % decompressedWidth != 0 ? rgbVals[i - 3] : 0;
          filterPix.Green = (i - 1) % decompressedWidth != 0 ? rgbVals[i - 2] : 0;
          filterPix.Blue  = (i - 1) % decompressedWidth != 0 ? rgbVals[i - 1] : 0;
          break;
        case UP:
          filterPix.Red   = (i - 49) > 0 ? rgbVals[i - 49] : 0;
          filterPix.Green = (i - 49) > 0 ? rgbVals[i + 1 - 49] : 0;
          filterPix.Blue  = (i - 49) > 0 ? rgbVals[i + 2 - 49] : 0;
          break;
        case AVERAGE:
          filterPix.Red   = (uint32_t) floor((((i - 49) > 0 ? rgbVals[i - 49] : 0) + ((i - 1) % decompressedWidth != 0 ? rgbVals[i - 3] : 0)) / 2) % 256;
          filterPix.Green = (uint32_t) floor((((i - 49) > 0 ? rgbVals[i + 1 - 49] : 0) + ((i - 1) % decompressedWidth != 0 ? rgbVals[i - 2] : 0)) / 2) % 256;
          filterPix.Blue  = (uint32_t) floor((((i - 49) > 0 ? rgbVals[i + 2 - 49] : 0) + ((i - 1) % decompressedWidth != 0 ? rgbVals[i - 1] : 0)) / 2) % 256;
          break;
        case PAETH:
            filterPix = calcPaeth(rgbVals, decompressedWidth, i);
          break;
        default:
          break;
      }

      rgbVals[i]     += filterPix.Red;
      rgbVals[i + 1] += filterPix.Green;
      rgbVals[i + 2] += filterPix.Blue;
      i += 3;
    }
  }
}

// Decompression works, note that if png size IDAT chunk has more than 16384 bytes uncompressed, then while loop will keep running til empty
// as well as subsequent IDAT chunks can occur, these two things are still not handled properly
// When multiple IDAT chunks, you need to concatenate data all together then inflate
void uncompressIDAT(std::ifstream &in, std::vector<uint8_t> *buffer, uint32_t width, uint32_t height) {
  // For some reason rgbVals as a vector cashes on inflate end so leaving as is
  uint8_t rgbVals[CHUNK_SIZE];

  //zlib struct needed for decompression (inflate is decompression, deflate is compression)

  z_stream infstream;
  infstream.zalloc = Z_NULL;
  infstream.opaque = Z_NULL;
  infstream.avail_in = (uInt)buffer->size(); // size of input
  infstream.next_in = (Bytef *)buffer->data(); // input char array
  infstream.avail_out = (uInt)CHUNK_SIZE; // size of output
  infstream.next_out = (Bytef *)rgbVals; // output char array

  inflateInit(&infstream);

  while(infstream.avail_in != 0) {
    inflate(&infstream, Z_NO_FLUSH);
  }

  applyFilterMethod(rgbVals, width, height);
  inflateEnd(&infstream);
}

void parseICCP(std::ifstream &in, uint32_t chunkLength) {
  std::vector<uint8_t> buffer(chunkLength);

  in.read((char *) buffer.data(), chunkLength);
}

void readPng(std::string pngFile) {
  std::ifstream in;
  struct IHDR ihdr;
  uint8_t validPngMask = 0;
  uint32_t chunkLength;
  uint32_t crc;
  std::vector<uint8_t> chunkType(5);
  in.open(pngFile.c_str(), std::ios::binary);
  std::vector<uint8_t> signature(9);
  std::vector<uint8_t> idatBuffer;

  if (!in) {
    exit(0);
  }

  // Header is 8 bytes long, every png has this, use to confirm file format is png
  in.read((char *) signature.data(), sizeof(uint64_t));
  signature[8] = '\0';

  if (strcmp((char *)signature.data(), (char *)png.data()) != 0) {
    std::cout << "Not a PNG format" << std::endl;
    exit(0);
  }

  while (strcmp((char *)chunkType.data(), "IEND\0") != 0 && in.good()) {
    // Format for data is 4 bytes to give length of chunk buffer
    // 4 bytes for chunk type
    // X bytes of chunk data
    // Topped off with 4 bytes of crc
    // This below reads the IHDR which should follow right after header
    in.read((char*) &chunkLength, sizeof(uint32_t));
    chunkLength = htonl(chunkLength);
    in.read((char *) chunkType.data(), sizeof(uint32_t));
    chunkType[4] = '\0';

    // IDAT chain is broken so now uncompress all data collected
    if ((((validPngMask & IDAT_CHAIN) >> 3) == 1) && (strcmp((char *) chunkType.data(), "IDAT\0") != 0)) {
      validPngMask &= 0xF7;
      //temp
      uncompressIDAT(in, &idatBuffer, ihdr.width, ihdr.height);
      idatBuffer.clear();
    }

    if ((validPngMask & IHDR_MASK) == 0 && strcmp((char *) chunkType.data(), "IHDR\0") != 0) {
      std::cout << "Error! Invalid PNG file, IHDR chunk did not follow PNG signature." << std::endl;
      exit(0);
    } 
    else if ((validPngMask & IHDR_MASK) == 0 && strcmp((char *) chunkType.data(), "IHDR\0") == 0) {
      validPngMask |= IHDR_MASK;
      parseIHDR(in, chunkLength, &ihdr);
    }
    else if (strcmp((char *) chunkType.data(), "IDAT\0") == 0) {
      std::vector<uint8_t> tempBuffer(chunkLength);
      in.read((char *) tempBuffer.data(), chunkLength);
      idatBuffer.insert(idatBuffer.end(), tempBuffer.begin(), tempBuffer.end());

      if ((validPngMask & IDAT_MASK) == 0) {
        validPngMask |= IDAT_MASK;
      }

      // Start of the IDAT chain, start appending all data to buffer
      if ((validPngMask & IDAT_CHAIN) == 0) {
        validPngMask |= IDAT_CHAIN;
      }
    }
    else if (strcmp((char *) chunkType.data(), "iCCP\0") == 0) {
      if ((validPngMask & IDAT_MASK) != 0) {
        std::cout << "Error! iCCP chunk must appear before first IDAT chunk" << std::endl;
        exit(0);
      }
       //Temp
       parseICCP(in, chunkLength);
    } else {
      //Temp
      parseICCP(in, chunkLength);
    }

    in.read((char *) &crc, sizeof(uint32_t));
  }

  if (strcmp((char *) chunkType.data(), "IEND\0") == 0) {
    validPngMask |= IEND_MASK;
  }

  in.close();
}
