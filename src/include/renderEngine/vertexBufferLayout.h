#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include <iostream>

#include "utility/net_utility.h"
#include "glcommon.h"

struct VertexBufferElement {
    uint32_t type;
    uint32_t count;
    bool normalized;
};

class VertexBufferLayout {
  public:
    VertexBufferLayout() : mStride(0) {}
    ~VertexBufferLayout() {}

    /* Function:    push
       Description: Pushes new layout to list
       Parameters:  uint32_t - Number of elements describing VBO for VAO to understand
       Returns:     None 
    */
    void push(const uint32_t cCount, const uint16_t cType, const bool cNormalized) {
        mElements.push_back({cType, cCount, cNormalized});

        switch(cType) {
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

    static int32_t getElementSize(const uint16_t cType) {
        switch(cType) {
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


    /* Function:    getElements
       Description: Returns list of elements for VAO
       Parameters:  None
       Returns:     vector - List of element data describing VBO
    */
    inline const std::vector<VertexBufferElement> getElements() const {return mElements;}

    /* Function:    getStride
       Description: Returns the stride of VBO
       Parameters:  None
       Returns:     uint32_t - Stride of VBO 
    */
    inline uint32_t getStride() const {return mStride;}
  private:
    std::vector<VertexBufferElement> mElements; 
    uint32_t mStride;
};

#endif