#ifndef GIF_READER_HPP
#define GIF_READER_HPP

#include <string>
#include <vector>
#include <memory>

struct __attribute__((packed)) GifHeader
{
  uint8_t Signature[4]; //!< Signature of the file, should always be GIF (Decimal: 47, 49, 46)
  uint8_t Version[4]; //!< Version of file, most commonly 89a (Decimal: 38, 39, 61) or 87a (Decimal: 38, 37, 61)
};

struct __attribute__((packed)) LogicalScreenDescriptor
{
  uint16_t CanvasWidth; //!< Width of Canvas not usually important to rendering a GIF
  uint16_t CanvasHeight; //!< Height of Canvas not usually important to rendering a GIF
  //! Contains the following bitmap
  //! MSB Bit 7: If set, global color table will follow
  //! Bit 6-4: Meaningful if there is a global color table, represents number of bits per pixel for byte dec val + 1 = number of colors supported
  //! Bit 3: Sort Flag, if set the colors in the global color table is sorted in decreasing importance.
  //! Bit 2-0: Size of global color table 2^(Byte Dec val + 1) size of table
  uint8_t PacketField;
  uint8_t BkgndColorIdx; //!< Hardly used, but on valid if global color table set to 1. Used for rendering canvas of gifs
  uint8_t PxlAspectRatio; //!< Not used in modern days, seems to be an artifact of analog days. LestMedia ignores this
};

//! Optional Extension for GIF89
struct __attribute__((packed)) GraphicsControlExtension
{
  //! MSB Bits 7-5: Reserved for future use
  //! Bits 4-2: Disposal Method
  //! Bit 1: User Input Flag
  //! Bit 0: Transparent Color Flag
  uint8_t PacketField;
  uint16_t DelayTime; //!< Delay between each Frame in hundredths of a second (10 = 100ms)
  uint8_t TransparentColorIndex; //!<
};

//! Data for each image, each image begins with an image separator
struct __attribute__((packed)) ImageDescriptor
{
  uint16_t ImageLeft; //!< X pos of image can be ignored when rendering
  uint16_t ImageTop; //!< Y pos of image can be ignored when rendering
  uint16_t ImageWidth; //!< Image Width
  uint16_t ImageHeight; //!< Image Height

  //! MSB Bit 7: Local Color Table Flag Specifies that the image associated with the Descriptor uses local color table instead of gloabl color table
  //! Bit 6: Interlace Flag 
  //! Bit 5: Sort Flag
  //! Bit 4-3: Reserved for future use
  //! Bit 2-0: Size of local color table
  uint8_t PacketField;
};

struct ImagePage
{
  ImageDescriptor ImgDesc; //!< Description of the Image
  std::shared_ptr<std::vector<uint8_t>> pColorTable; //!< Global Color Table or Local Color Table depending on the Image Descriptor
  std::shared_ptr<GraphicsControlExtension> pGfxCtrl; //!< Gfx Control Extensionns
  std::vector<uint8_t> Pixels; //!< Pixel RGB Data
};

//! @class Reads a GIF file and extracts the properties
class GifReader
{
public:
  //! @brief Default Constructor
  GifReader();

  //! @brief Default Destructor
  ~GifReader() = default;

  //! @brief Reads in a GIF file and extracts the properties
  //!
  //! @param[in] crFile GIF File
  //!
  //! @retval -1 On failure to read GIF file
  //! @retval 0 On Success
  int read(const std::string& crFile);

  //! @brief Returns a vector filled with GIF image data
  //!
  //! @return Vector of Images
  std::vector<ImagePage> getImages() const;
private:
  //! @brief Reads the Logical Screen Descriptor Block
  //!
  //! @param[in] rIfStream File Stream to read from
  //!
  //! @retval -1 Indicates failure
  //! @retval 0 On success
  int readLogicalScreenDescriptor(std::ifstream& rIfStream);

  //! @brief Reads the global color table
  //!
  //! @param[in] rIfStream File Stream to read from
  //! @param[out] rColorTable Color Table
  //! @param[in] cTableSize Bit Representation of Table size from packetfield
  //!
  //! @retval -1 On Failure
  //! @retval 0 On Success
  int readColorTable(std::ifstream& rIfStream, std::vector<uint8_t>& rColorTable, const uint8_t cTableSize);

  //! @brief Reads in an extension block
  //!
  //! @param[in] rIfStream File Stream to read from
  //!
  //! @retval -1 On Failure
  //! @retval 0 On Success
  int extBlockHandler(std::ifstream& rIfstream);

  //! @brief Reads in an image descriptor block
  //!
  //! @param[in] rIfStream File Stream to read from
  //!
  //! @retval -1 On Failure
  //! @retval 0 On Success
  int imageDescHandler(std::ifstream& rIfstream);

  //! @brief Reads in a Graphics Control Extension block
  //!
  //! @param[in] rIfStream File Stream to read from
  //! @param[in] cBlockSize Block Size to read
  //!
  //! @retval -1 On Failure
  //! @retval 0 On Success
  int readGfxCtrlExt(std::ifstream& rIfstream, const uint8_t cBlockSize);

  //! @brief Reads in a Plain Text Extension block
  //! @note LestMedia reads past this block and does nothing with the data
  //!
  //! @param[in] rIfStream File Stream to read from
  //! @param[in] cBlockSize Block Size to read
  //!
  //! @retval -1 On Failure
  //! @retval 0 On Success
  int readPlainTextExt(std::ifstream& rIfstream, const uint8_t cBlockSize);

  //! @brief Reads in a Comment Extension block
  //! @note LestMedia reads past this block and does nothing with the data
  //!
  //! @param[in] rIfStream File Stream to read from
  //! @param[in] cBlockSize Block Size to read
  //!
  //! @retval -1 On Failure
  //! @retval 0 On Success
  int readCommentExt(std::ifstream& rIfstream, const uint8_t cBlockSize);

  //! @brief Reads in a Application Extension block
  //! @note LestMedia reads past this block and does nothing with the data
  //!
  //! @param[in] rIfStream File Stream to read from
  //! @param[in] cBlockSize Block Size to read
  //!
  //! @retval -1 On Failure
  //! @retval 0 On Success
  int readApplExt(std::ifstream& rIfstream, const uint8_t cBlockSize);

  //! @brief Decompresses the code stream in a gif
  //!
  //! @param[in] cLzwMinCode Min Code to use for LZW decompression
  //! @param[in] crCodeStream Code stream to decompress
  //! @param[out] rPixelBytes Vector to store RGB pixel bytes
  //!
  //! @retval -1 On Failure
  //! @retval 0 On Success
  int LZWDecompression(const uint8_t cLzwMinCode, const std::vector<uint8_t>& crCodeStream, std::vector<uint8_t>& rPixelBytes);

  //! Gif Header Properties
  GifHeader mGifHeader;

  //! Logical Screen Descriptor Properties
  LogicalScreenDescriptor mScrnDesc;

  //! List of image data
  std::vector<ImagePage> mImages;

  //! Determines if Global Color Table exists in GIF
  bool mHasGlobalColorTable = false;

  //! Number of bits for color
  uint8_t mColorResolution = 0;

  //! Determines the way the global color table is sorted
  bool mSorted = false;

  //! Global Color Table, will be size 0 if not present
  std::shared_ptr<std::vector<uint8_t>> mpGlobalColorTable;

  //! Pending Graphics Control Extension properties to be added to the next Image Frame
  std::shared_ptr<GraphicsControlExtension> mpPendingGfxCtrl;
};

#endif