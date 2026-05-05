#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <array>
#include <functional>

#include "vertex.hpp"
#include "drawable/I_Sprite.hpp"

// Eventually we will deprecate a sprite from knowing it's position.
// This structure allows us to render a sprite directly for easy testing purposes
class Sprite : public I_Sprite
{
  public:
    //! @brief Default Constructor
    Sprite();

    //! @brief Copy Constructor
    Sprite(const Sprite& rSprite);

    //! @brief Assignment Operator
    //!
    //! @param[in] rhs Object to assign to this pointer
    //!
    //! @return Sprite reference
    Sprite& operator=(const Sprite& rhs);

    //! @brief Sprite Constructor
    //!
    //! @param[in] cpFrameSource Texture of Sprite
    //! @param[in] crBox     Dimensions of Sprite
    //! @param[in] cInvert Invert sprite
    Sprite(const std::shared_ptr<FrameSource> cpFrameSource, const Rect<float>& crBox, const bool cInvert = true);

    //! @brief Sprite Constructor
    //!
    //! @param[in] crColor Color of Sprite
    //! @param[in] crBox Dimensions of Sprite
    Sprite(const lg::Color& crColor, const Rect<float>& crBox);

    //! @brief Default Destructor
    ~Sprite() = default;


    const Texture2D& getTexture() const;
  
    //! @brief Moves Sprite
    //!
    //! @param[in] crMoveVector Vector to add to Sprite
    void movePos(const glm::vec2& crMoveVector) override;
  
    //! @brief Sets the Sprite Positition
    //!        Note: This works by setting the Center Position
    //!
    //! @param[in] crPos New Sprite Position
    //!
    //! @return Sprite Reference to chain calls
    Sprite& setPos(const glm::vec2& crPos) override;
    
    //! @brief Sets Size of Sprite
    //!
    //! @param[in] crSize New Sprite Size
    //!
    //! @return Sprite reference to chain calls
    Sprite& resize(const glm::vec2& crSize) override;
    Sprite& setTransform(const Transform& crTransform) override;

    //! @brief Sets FrameSource for Sprite
    //! TODO: Add the size of the texture to set
    //!
    //! @param[in] cpFrameSource  FrameSource
    //! @param[in] cInvert    Inverts texture coordinates
    //!
    //! @return Sprite Reference to chain calls
    Sprite& setFrameSource(const std::shared_ptr<FrameSource> cpFrameSource, const bool cInvert=false);
    Sprite& setBox(const Rect<float>& crBox) override;
    
    //! @brief Gets the Size of Sprite
    //!
    //! @return Size of Sprite
    glm::vec2 getSize() const;
    
    //! @brief Returns position of Sprite
    //!
    //! @return Sprite Position
    glm::vec2 getPos() const;
    
    //! @brief Sets Color of Sprite
    //!        Only useful for Sprites without Textures
    //!
    //! @param[in] crColor Color to set Sprite
    //!
    //! @return Sprite Reference to chain calls
    Sprite& setColor(const lg::Color& crColor) override;
    
    //! @brief Gets the Box corresponding to Sprite
    //!
    //! @return Box of Sprite 
    const Rect<float>& getBox() const;

    //! @brief Setst the Layer for the Sprite
    //!        Handles Reregistering into Map of Drawables for sorting
    //!
    //! @param cLayer Layer to set Sprite Draw, Higher Layers means Quad will render over lower Layer Quads
    //!        Think of Layer = 0 as Background
    void setLayer(const uint32_t cLayer);
  
    //! @brief Draws the Sprite
    //!
    //! @return None
    void draw();

    Sprite& update(const float cDt) override;

    // void draw(const Transform& crTransform) override;
    Rect<float> getGlobalBounds(const OrthCamera& crCamera) const;
    lg::Color getColor() const;
  protected:
    void drawUntexturedSprite2(const Transform& crTransform);
    void drawTexturedSprite2(const Transform& crTransform);
    void drawUntexturedSprite();
    void drawTexturedSprite();

    //! @brief Registers lambda function to bind member functions to std::function
    //!
    //! @param Callback Lambda function to register member function
    //!
    //! @return Function pointer 
    std::function<void(const Transform&)> RegisterDrawCall(std::function<void(const Transform&)> Callback);

    glm::vec2 mPrevPos;

    //! Render vertex data
    std::array<Vertex, sNumQuadVerts> mVertexes;
    std::function<void()> mDrawFunc;
    lg::Color mColor;
    bool mInvert = false;
};

#endif