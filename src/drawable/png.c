#include "png.h"

#define WINDOW_BITS 47

const std::vector<uint8_t> png = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, '\0'};

/* Function:    parseIHDR
   Description: Parses IHDR from png file
   Parameters:  ifstream - file descriptor for file we are reading
                uint32_t - The amount of bytes to read
                struct IHDR - IHDR struct to store values from parsed IHDR
   Returns:     None
 */
void parseIHDR(std::ifstream &in, uint32_t chunkLength, struct IHDR *ihdr) {
  in.read((char *) ihdr, chunkLength);
  /* There is no endian issues for 1 byte values which is why only width and height needs to be rearranged */
  ihdr->width = htonl(ihdr->width);
  ihdr->height = htonl(ihdr->height);

  if ((ihdr->width == 0) || (ihdr->height == 0)) {
    std::cout << "Error! Invalid image dimensions." << std::endl;
    exit(0);
  }
}

/* Function:    subPixelRGB
   Description: subtracts the RGB vals from two Pixels
   Parameters:  struct RGB - Pixel 1 RGB values
                struct RGB - Pixel 2 RGB values
   Returns:     struct RGB - New pixel RGB values
 */
struct RGB subPixelRGB(struct RGB pixel1, struct RGB pixel2) {
  return {(uint8_t)((pixel1.Red - pixel2.Red)), (uint8_t)((pixel1.Green - pixel2.Green)),
          (uint8_t)((pixel1.Blue - pixel2.Blue))};
}

/* Function:    addPixelRGB
   Description: Adds the RGB vals from two Pixels
   Parameters:  struct RGB - Pixel 1 RGB values
                struct RGB - Pixel 2 RGB values
   Returns:     struct RGB - New pixel RGB values
 */
struct RGB addPixelRGB(struct RGB pixel1, struct RGB pixel2) {
  return {(uint8_t)((pixel1.Red + pixel2.Red)), (uint8_t)((pixel1.Green + pixel2.Green)),
          (uint8_t)((pixel1.Blue + pixel2.Blue))};
}

/* Function:    calcPaethByte
   Description: Paeth Algorightm requires it to be run on each RGB byte
   Parameters:  uint8_t - A pixel RGB byte
                uint8_t - B pixel RGB byte
                uint8_t - C pixel RGB byte
   Returns:     uint8_t - Correct predictor pixel
 */
uint8_t calcPaethByte(uint8_t a, uint8_t b, uint8_t c) {
  int32_t p, pa, pb, pc;
  // int32_t type cast needed because values can be negative
  p = (int32_t)a + (int32_t)b - (int32_t)c;
  pa = abs(p - (int32_t)a);
  pb = abs(p - (int32_t)b);
  pc = abs(p - (int32_t)c); 

  if ((pa <= pb) && (pa <= pc)) {
    return a;
  }
  else if (pb <= pc) {
    return b;
  }
  else {
    return c;
  }
}

/* Function:    paethRGBBitDepth8
   Description: Paeth Algorightm requires it to be run on each RGB byte
   Parameters:  std::vector<uint8_t> - Structure containing unfiltered img data
                uint32_t - Size of scanline row
                uint8_t  - Number of bytes per pixel
   Returns:     struct RGB - Unfiltered Pixel Color
 */
struct RGB paethRGBBitDepth8(std::vector<uint8_t> imgData, uint32_t scanlineSize, uint8_t rgbSize) {
  /*
  Calculates the PAETH algorithm.
  The PAETH algorithm works on bytes, which means that one byte values will not work.
  For example you need to add two rgb values and compare that with another value.
  Assume 1 byte values 255 and 1. 255 + 1 overflows a uint8_t and results in 0.
  The above would mean that 255 + 1 <= 255 which is wrong in the paeth algorithm.
  
  To Overcome this I converted the rgbs into an integer as 0x0000RRRRGGGGBBBB
  This allows us to add integers without worrying about overflows.
*/
  struct RGB a, b, c, pr;
  const uint32_t imgDataSize = imgData.size();
  const uint32_t ULPix = imgDataSize - (scanlineSize + rgbSize);
  const uint32_t leftBound = imgDataSize % scanlineSize;
  const int32_t upperBound = imgDataSize - scanlineSize;

  /* The below blocks gathers the pixel RGB to the left of the current index, the Pixel RGB to the upper left of the current index,
     and the Pixel RGB above the current index
  */
  a.Red   = (leftBound != 0) ? imgData[imgDataSize - rgbSize] : 0;
  a.Green = (leftBound != 0) ? imgData[imgDataSize - (rgbSize - 1)] : 0;
  a.Blue  = (leftBound != 0) ? imgData[imgDataSize - (rgbSize - 2)] : 0;

  b.Red   = (upperBound >= 0) ? imgData[upperBound] : 0;
  b.Green = (upperBound >= 0) ? imgData[upperBound + 1] : 0;
  b.Blue  = (upperBound >= 0) ? imgData[upperBound + 2] : 0;

  c.Red   = (leftBound != 0) && (upperBound >= 0) ? imgData[ULPix] : 0;
  c.Green = (leftBound != 0) && (upperBound >= 0) ? imgData[ULPix + 1] : 0;
  c.Blue  = (leftBound != 0) && (upperBound >= 0) ? imgData[ULPix + 2] : 0;

  pr.Red   = calcPaethByte(a.Red, b.Red, c.Red);
  pr.Green = calcPaethByte(a.Green, b.Green, c.Green);
  pr.Blue  = calcPaethByte(a.Blue, b.Blue, c.Blue);
  return pr;
}

/* Function:    rgbBitDepth8
   Description: Iterates through buffer data applying the correct filter on decompressed IDAT chunk data
   Parameters:  std::vector<uint8_t> - Concatenated decompressed IDAT data
                std::vector<uint8_t> - Structure containing unfiltered img data
                struct IHDR - Png information for performing calculations
   Returns:     None
 */
void rgbBitDepth8(std::vector<uint8_t> rgbData, std::vector<uint8_t> &imgData, struct IHDR ihdr) {
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
  struct RGB filterPix;
  uint8_t filterValue = 0;
  uint8_t rgbSize = (ihdr.colorType == RGBTRIP) ? RGBSIZE : RGBASIZE;
  uint32_t scanlineSize = (ihdr.width * rgbSize);
  uint16_t mod = 256;
  uint32_t imgDataSize = 0;
  uint32_t leftBound = 0;
  int32_t upperBound = 0;

 for (int i = 0; i < (int) rgbData.size();) {
    imgDataSize = imgData.size();
    leftBound   = imgDataSize % scanlineSize;
    upperBound  = imgDataSize - scanlineSize;

    if (i % (scanlineSize + 1) == 0) {
      filterValue = rgbData[i];
      i ++;
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
          filterPix.Red   = (leftBound != 0) ? imgData[imgDataSize - rgbSize] : 0;
          filterPix.Green = (leftBound != 0) ? imgData[imgDataSize - (rgbSize - 1)] : 0;
          filterPix.Blue  = (leftBound != 0) ? imgData[imgDataSize - (rgbSize - 2)] : 0;
          break;
        case UP:
          filterPix.Red   = (upperBound >= 0) ? imgData[upperBound] : 0;
          filterPix.Green = (upperBound >= 0) ? imgData[upperBound + 1] : 0;
          filterPix.Blue  = (upperBound >= 0) ? imgData[upperBound + 2] : 0;
          break;
        case AVERAGE:
          filterPix.Red   = (uint32_t) floor((((upperBound >= 0) ? imgData[upperBound] : 0)     + ((leftBound != 0) ? imgData[leftBound - rgbSize] : 0)) / 2) % mod;
          filterPix.Green = (uint32_t) floor((((upperBound >= 0) ? imgData[upperBound + 1] : 0) + ((leftBound != 0) ? imgData[leftBound - (rgbSize - 2)] : 0)) / 2) % mod;
          filterPix.Blue  = (uint32_t) floor((((upperBound >= 0) ? imgData[upperBound + 2] : 0) + ((leftBound != 0) ? imgData[leftBound - (rgbSize - 2)] : 0)) / 2) % mod;
          break;
        case PAETH:
            filterPix = paethRGBBitDepth8(imgData, scanlineSize, rgbSize);
          break;
        default:
          break;
      }

      imgData.push_back((rgbData[i] + filterPix.Red) % mod);
      imgData.push_back((rgbData[i + 1] + filterPix.Green) % mod);
      imgData.push_back((rgbData[i + 2] + filterPix.Blue) % mod);

      if (rgbSize == RGBASIZE)
        imgData.push_back(rgbData[i + 3]);
  
      i += rgbSize;
    }
  }
}

/* Function:    handlePngColorType
   Description: Handles different colortype PNG configurations
   Parameters:  std::vector<uint8_t> - Concatenated decompressed IDAT data
                std::vector<uint8_t> - Structure containing unfiltered img data
                struct IHDR - Png information for performing calculations
   Returns:     None
 */
void handlePngColorType(std::vector<uint8_t> rgbData, std::vector<uint8_t> &imgData, struct IHDR ihdr) {
  switch (ihdr.colorType) {
    case 2:
    case 6:
    // fall through due to rgbBitDepth8 function being generic enough to capture
      if (ihdr.bitDepth == 8)
        rgbBitDepth8(rgbData, imgData, ihdr);
      break;
    default:
      std::cout << "ColorType not implemented" << std::endl;
      exit(0);
  }
}

/* Function:    uncompressIDAT
   Description: Decompresses IDAT chunk data and fills a buffer with the data
   Parameters:  std::vector<uint8_t> - Concatenated uncompressed IDAT data
                std::vector<uint8_t> - Concatenated decompressed IDAT data
   Returns:     None
 */
void uncompressIDAT(std::vector<uint8_t> buffer, std::vector<uint8_t> &decompressedData) {
  // Decompression works, note that if png size IDAT chunk has more than 16384 bytes uncompressed, then while loop will keep running til empty
  // as well as subsequent IDAT chunks can occur, these two things are still not handled properly
  // When multiple IDAT chunks, you need to concatenate data all together then inflate
  std::vector<uint8_t> decompressedChunk(CHUNK_SIZE);
  int8_t error = 0;

  //zlib struct needed for decompression (inflate is decompression, deflate is compression)

  z_stream infstream;
  infstream.zalloc = Z_NULL;
  infstream.zfree = Z_NULL;
  infstream.opaque = Z_NULL;
  infstream.avail_in = (uInt)buffer.size(); // size of input
  infstream.next_in = (Bytef *)buffer.data(); // input char array

  /* WINDOW_BITS = 47 since this tells zlib to automatically check if 
     gzip or zlib header exists in decompressed data
  */ 
  inflateInit2(&infstream, WINDOW_BITS);

  do {
    infstream.avail_out = (uInt)decompressedChunk.size(); // size of output
    infstream.next_out = (Bytef *)decompressedChunk.data(); // output char array
    error = inflate(&infstream, Z_NO_FLUSH);

    if ( error == Z_DATA_ERROR || error == Z_MEM_ERROR) {
      exit(0);
    }

    decompressedData.insert(decompressedData.end(), decompressedChunk.begin(), decompressedChunk.end());
  } while(infstream.avail_in != 0);

  inflateEnd(&infstream);
}

/* Function:    parseICCP
   Description: Parses ICCP chunk, but currently doesn't do that, just used to parse items
                that are not IHDR and IDAT from png
   Parameters:  ifstream - File descriptor to read data from
                uint32_t - Amount of bytes to read
   Returns:     None
 */
void parseICCP(std::ifstream &in, uint32_t chunkLength) {
  std::vector<uint8_t> buffer(chunkLength);

  in.read((char *) buffer.data(), chunkLength);
}

/* Function:    readPng
   Description: Parses an entire png file and stores rgb values to recreate img
   Parameters:  string - Location of file to read data from
                struct IHDR - Png information for performing calculations
   Returns:     std::vector<uint8_t> - Unfiltered IMG data
 */
std::vector<uint8_t> readPng(std::string pngFile, struct IHDR &pihdr) {
  std::ifstream in;
  std::vector<uint8_t> finalImgData, decompressedData;
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
      uncompressIDAT(idatBuffer, decompressedData);
      handlePngColorType(decompressedData, finalImgData, ihdr);
      idatBuffer.clear();
      decompressedData.clear();
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

  pihdr = ihdr;

  return finalImgData;
}