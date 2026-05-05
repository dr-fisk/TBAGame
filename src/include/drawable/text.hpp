#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>
#include <array>
#include <cstdint>

#define GLM_FORCE_CTOR_INIT
#include "vertex.hpp"
#include "resource/font.hpp"
#include "drawable/dot.hpp"
#include "shapes/rect.hpp"
#include "glm/vec2.hpp"
#include "renderer/camera.hpp"

class Text : public Dot
{
  public:
    //! @brief Default Constsructor
    //!
    //! @return Text Object
    Text();

    //! @brief Text Constructor
    //!
    //! @param[in]  crFont         Font Object to be used when rendering Text
    //! @param[in]  crText         String to be rendered
    //! @param[in]  cCharSize      Font Size
    //!
    //! @return Text Object 
    Text(const Font& crFont, const std::string& crText, const uint8_t cCharSize=12);
    
    //! @brief Updates Text to be rendered
    //!
    //! @param[in] crString Text to be rendered
    //!
    //! @return None
    Text& setString(const std::string& crText);

    //! @brief Get Texture for Drawable
    //!
    //! @return Texture
    const Texture2D& getTexture() const;

    //! @brief Moves Position by adding x and y values
    //!
    //! @param[in] crMoveVector Vector values to move Text
    //!
    //! @return None
    void movePos(const glm::vec2& crMoveVector);

    //! @brief Sets Text Position
    //!
    //! @param[in] crPos New Text Position
    //!
    //! @return None
    Text& setPos(const glm::vec2& crPos);
    
    //! @brief  Attaches font to text
    //!
    //! @param[in] crFont 
    //!
    //! @return None
    Text& setFont(const Font& crFont);

    //! @brief Sets the font size
    //!
    //! @param[in] cCharSize Font size in pixels
    //! 
    //! @return Text Reference 
    Text& setFontSize(const uint8_t cCharSize);

    //! @brief Enables/disables linewrap functionality
    //!
    //! @param[in] cEnable Enable/Disable boolean
    //!
    //! @return Text reference to chain setters
    Text& setLineWrap(const bool cEnable);

    //! @brief Inserts string to text object
    //!
    //! @param[in] crString String to append
    //! @param[in] cIndex   Index to append string to
    //!
    //! @return None
    void insertString(const std::string& crString, const size_t cIndex);

    //! @brief Appends string to end of text object
    //!
    //! @param[in] crString String to append
    //!
    //! @return None 
    void appendString(const std::string& crString);
    
    //! @brief Sets the fill color for text
    //!
    //! @param[in] crColor Fill color
    //! 
    //! @return Text reference to chain setters 
    Text& setColor(const lg::Color &crColor);
    
    //! @brief Gets the length of string member variable
    //!
    //! @return Length of String member variable 
    size_t getLength() const;
    
    //! @brief Returns top left of Text Position
    //!
    //! @return Text Position 
    glm::vec2 getPos() const;
    
    //! @brief Grabs Text String
    //!
    //! @return Text
    std::string& getString();

    //! @brief Grabs Text String
    //!
    //! @return Text
    const std::string& getString() const;
    
    //! @brief Gets Size of Text
    //!
    //! @return Size of Text
    glm::vec2 getSize() const;

    //! @brief Get the Font Size
    //!
    //! @return Font size 
    uint8_t getFontSize() const;

    //! @brief Gets the position of the character at a given index
    //! @throw Throws if index out of bounds
    //!
    //! @param[in] cCharIndex Index of character to get position from
    //! 
    //! @return Character position 
    glm::vec2 getCharPos(const int cCharIndex) const;

    //! @brief Gets font character size
    //! @throw Throws if index out of bounds
    //!
    //! @param[in] cCharIndex Index of character to get size of
    //!
    //! @return character size 
    glm::vec2 getCharSize(const int cCharIndex) const;

    //! @brief Draws the Text
    //!
    //! @return None
    void draw();

    //! @brief Draws character at index
    //! @throw If index is out of bound
    //!
    //! @param[in] cCharIdx Index of character to draw
    //!
    //! @return None
    void draw(const int cCharIdx);

    //! @brief Default destructor
    ~Text() = default;

    Rect<float> getGlobalBounds(const OrthCamera& crCamera) const;
    std::vector<Rect<float>> getBoundingBoxes() const;
    void updateGeometry();
  private:
    //! @brief Creates layout of Text
    //!
    //! @return None
    void gridfitText(const glm::vec2& crTopLeft);
    
    //! @brief Updates vertexes to fill color
    //!
    //! @param[out] rVertexes Vertexes to set fill color on
    //!
    //! @return None
    void updateQuadColor(std::array<Vertex, sNumQuadVerts>& rVertexes);

    struct TextVertexData
    {
      glm::vec2 Pos;
      glm::vec2 Size;
      std::array<Vertex, sNumQuadVerts> Vertexes;
    };
  
    const Font* mpFont;
    std::string mText;
    std::vector<TextVertexData> mTextVertexes;
    Rect<float> mBox;
    glm::vec2 mSize;
    int32_t mLineWrap = -1;
    int32_t mLineSpace;
    uint8_t mCharSize = 12;
    uint16_t mAdvancedWidth;
    int32_t mCapHeight;
    const Texture2D* mpTexture;
    lg::Color mColor = lg::Black;
};

#endif