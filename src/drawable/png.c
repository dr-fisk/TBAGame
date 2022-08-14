#include "png.h"


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
  /*std::ofstream f("ihdr.txt");
  f << ihdr->width << std::endl;
  f << ihdr->height << std::endl;
  f <<  (unsigned int)ihdr->bitDepth << std::endl;
  f <<  (unsigned int)ihdr->colorType << std::endl;
  f <<  (unsigned int)ihdr->compressionMethod << std::endl;
  f <<  (unsigned int)ihdr->filterMethod << std::endl;
  f <<  (unsigned int)ihdr->interfaceMethod << std::endl;
  f.close();*/
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

/* Function:    convertRGBToInt
   Description: Converts pixel RGB values to an int for Paeth Algorithm
   Parameters:  struct RGB - Pixel RGB values
   Returns:     int32_t - Byte value to be used in Paeth Algorithm
 */
int32_t convertRGBToInt(struct RGB pixel) {
  int32_t rgb = pixel.Red + pixel.Green + pixel.Blue;
  return rgb;
}

/* Function:    calcPaeth
   Description: Applies the Paeth Algorithm to the current row of pixels
   Parameters:  uint8t * - Buffer data containing decompressed png IDAT chunk values
                uint32_t - The end of the a row of pixels in the buffer
                int32_t  - Current index in the buffer data
   Returns:     struct RGB - RGB values to be used to filter pixel at index
 */
struct RGB calcPaeth(uint8_t *rgbVals, uint32_t width, int32_t index) {
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
  const int32_t ULPix = width + 3;
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

  b.Red   = (index - width) > 0 ? rgbVals[index - width] : 0;
  b.Green = (index - width) > 0 ? rgbVals[index + 1 - width] : 0;
  b.Blue  = (index - width) > 0 ? rgbVals[index + 2 - width] : 0;

  c.Red   = (index - ULPix) > 0 ? rgbVals[index - ULPix] : 0;
  c.Green = (index - ULPix) > 0 ? rgbVals[index + 1 - ULPix] : 0;
  c.Blue  = (index - ULPix) > 0 ? rgbVals[index + 2 - ULPix] : 0;

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

/* Function:    applyFilterMethod
   Description: Iterates through buffer data applying the correct filter on decompressed IDAT chunk data
   Parameters:  uint8t * - Buffer data containing decompressed png IDAT chunk values
                uint32_t - The end of the a row of pixels in the buffer
                uint32_t - The end of the a col of pixels in the buffer
   Returns:     None
 */
void applyFilterMethod(uint8_t *rgbVals, uint32_t width, uint32_t height, uint32_t bytes) {
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
  uint32_t decompressedWidth = (width * 3) + 1;

 for (int i = 0; i < bytes;) {
    if (i % decompressedWidth == 0) {
      filterValue = rgbVals[i];
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
          filterPix.Red   = (i - 1) % decompressedWidth != 0 ? rgbVals[i - 3] : 0;
          filterPix.Green = (i - 1) % decompressedWidth != 0 ? rgbVals[i - 2] : 0;
          filterPix.Blue  = (i - 1) % decompressedWidth != 0 ? rgbVals[i - 1] : 0;
          break;
        case UP:
          filterPix.Red   = (i - decompressedWidth) > 0 ? rgbVals[i - decompressedWidth] : 0;
          filterPix.Green = (i - decompressedWidth) > 0 ? rgbVals[i + 1 - decompressedWidth] : 0;
          filterPix.Blue  = (i - decompressedWidth) > 0 ? rgbVals[i + 2 - decompressedWidth] : 0;
          break;
        case AVERAGE:
          filterPix.Red   = (uint32_t) floor((((i - decompressedWidth) > 0 ? rgbVals[i - decompressedWidth] : 0) + ((i - 1) % decompressedWidth != 0 ? rgbVals[i - 3] : 0)) / 2) % 256;
          filterPix.Green = (uint32_t) floor((((i - decompressedWidth) > 0 ? rgbVals[i + 1 - decompressedWidth] : 0) + ((i - 1) % decompressedWidth != 0 ? rgbVals[i - 2] : 0)) / 2) % 256;
          filterPix.Blue  = (uint32_t) floor((((i - decompressedWidth) > 0 ? rgbVals[i + 2 - decompressedWidth] : 0) + ((i - 1) % decompressedWidth != 0 ? rgbVals[i - 1] : 0)) / 2) % 256;
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

/* Function:    uncompressIDAT
   Description: Decompresses IDAT chunk data and fills a buffer with the data
   Parameters:  ifstream - File descriptor to read data from
                vector<uint8_t> - Compressed IDAT chunk data
                uint32_t - The end of the a row of pixels in the buffer
                uint32_t - The end of the a col of pixels in the buffer
   Returns:     None
 */
void uncompressIDAT(std::ifstream &in, std::vector<uint8_t> buffer, std::vector<struct RGB> *finalImgData, uint32_t width, uint32_t height) {
  // Decompression works, note that if png size IDAT chunk has more than 16384 bytes uncompressed, then while loop will keep running til empty
  // as well as subsequent IDAT chunks can occur, these two things are still not handled properly
  // When multiple IDAT chunks, you need to concatenate data all together then inflate
  // For some reason rgbVals as a vector cashes on inflate end so leaving as is
  uint8_t rgbVals[CHUNK_SIZE];
  uint32_t inflateNums = 0;
  int8_t error = 0;

  //zlib struct needed for decompression (inflate is decompression, deflate is compression)

  z_stream infstream;
  infstream.zalloc = Z_NULL;
  infstream.zfree = Z_NULL;
  infstream.opaque = Z_NULL;
  infstream.avail_in = (uInt)buffer.size(); // size of input
  infstream.next_in = (Bytef *)buffer.data(); // input char array

  inflateInit2(&infstream, 47);
  //std::ofstream uf("unfiltered.txt");
 // std::ofstream f("filter.txt");

  do {
    infstream.avail_out = (uInt)CHUNK_SIZE; // size of output
    infstream.next_out = (Bytef *)rgbVals; // output char array
    error = inflate(&infstream, Z_NO_FLUSH);

    if ( error == Z_DATA_ERROR || error == Z_MEM_ERROR) {
      exit(0);
    }

    /*for(int i = 0; i < infstream.total_out - (inflateNums * CHUNK_SIZE);) {
      if (i % ((width * 3) + 1) != 0) {
        uf <<'(' <<  (unsigned int)rgbVals[i] << ',' << (unsigned int)rgbVals[i + 1] << ',' << (unsigned int)rgbVals[i + 2] <<')';
        i += 3;
      }
      else {
        uf << std::endl << "Filter: "  << (unsigned int) rgbVals[i] << '(' << i / 49 << ')' << std::endl;
        i ++;

      }
    }*/
    applyFilterMethod(rgbVals, width, height, abs((int)infstream.total_out - (int)(inflateNums * CHUNK_SIZE)));

    for(int i = 0; i < abs((int)infstream.total_out - (int)(inflateNums * CHUNK_SIZE));) {
      if (i % ((width * 3) + 1) != 0) {
        //f <<'(' <<  (unsigned int)rgbVals[i] << ',' << (unsigned int)rgbVals[i + 1] << ',' << (unsigned int)rgbVals[i + 2] <<')';
        finalImgData->push_back({(uint8_t)rgbVals[i], (uint8_t)rgbVals[i + 1], (uint8_t)rgbVals[i + 2]});
        i += 3;
      }
      else {
        i ++;
        //f << std::endl << i / 49 << std::endl;
      }
    }

    inflateNums ++;
  } while(infstream.avail_in != 0);

  inflateEnd(&infstream);
 // f.close();
 // uf.close();
  //exit(0);
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
   Returns:     None
 */
std::vector<struct RGB> readPng(std::string pngFile) {
  std::ifstream in;
  std::vector<struct RGB> finalImgData;
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
      uncompressIDAT(in, idatBuffer, &finalImgData, ihdr.width, ihdr.height);
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

  return finalImgData;
}
