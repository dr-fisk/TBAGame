#ifndef VERTEXBUFFERLAYOUT_HPP
#define VERTEXBUFFERLAYOUT_HPP

#include <iostream>
#include <vector>
#include <cstdint>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glcommon.hpp"

struct VertexBufferElement 
{
    uint32_t type;
    uint32_t count;
    bool normalized;
};

class VertexBufferLayout
{
  public:
    VertexBufferLayout() : mStride(0) {}
    VertexBufferLayout(std::initializer_list<VertexBufferElement> elements) : mElements(elements),  mStride(0)
    {
      calcStride();
    }
  
    ~VertexBufferLayout() = default;

    //! @brief Pushes new layout to list
    //! @param[in] cCount      Number of elements describing VBO for VAO to understand
    //! @param[in] cType       Data Type to add to layout
    //! @param[in] cNormalized Is Data that will be passed in normalized
    //!
    //! @return None
    void push(const uint32_t cCount, const uint16_t cType, const bool cNormalized)
    {
      mElements.push_back({cType, cCount, cNormalized});

      switch(cType)
      {
          case GL_FLOAT:
          case GL_INT:
          case GL_UNSIGNED_INT:
            mStride += sizeof(GLuint) * cCount;
            break;
          case GL_UNSIGNED_BYTE:
            mStride += sizeof(GLubyte) * cCount;
            break;
          default:
            std::cout << "Unsupported type in buffer layout." << std::endl;
            exit(-1);
      }
    }

    //! @brief Converts the Enum Type to a Byte Size
    //!
    //! @param[in] cType Type to convert into Size of Bytes
    //!
    //! @return Data Type size in bytes
    static int32_t getElementSize(const uint16_t cType)
    {
      switch(cType)
      {
        case GL_FLOAT:
        case GL_INT:
        case GL_UNSIGNED_INT:
          return sizeof(GLuint);
        case GL_UNSIGNED_BYTE:
          return sizeof(GLubyte);
        default:
          std::cout << "Unsupported type in buffer layout." << std::endl;
          exit(-1);
      } 
    }


    //! @brief Returns list of elements for VAO
    //!
    //!@return List of element data describing VBO
    inline const std::vector<VertexBufferElement> getElements() const {return mElements;}

    //! @brief Returns the stride of VBO
    //!
    //! @return Stride of VBO 
    inline uint32_t getStride() const {return mStride;}
  private:
    void calcStride()
    {
      for(const auto& elements : mElements)
      {          
        switch(elements.type)
        {
            case GL_FLOAT:
            case GL_INT:
            case GL_UNSIGNED_INT:
              mStride += sizeof(GLuint) * elements.count;
              break;
            case GL_UNSIGNED_BYTE:
              mStride += sizeof(GLubyte) * elements.count;
              break;
            default:
              std::cout << "Unsupported type in buffer layout." << std::endl;
              exit(-1);
        }
      }
    }

    std::vector<VertexBufferElement> mElements; 
    uint32_t mStride;
};

#endif