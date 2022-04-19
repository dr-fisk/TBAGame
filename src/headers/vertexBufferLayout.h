#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include "common.h"

struct VertexBufferElement {
    uint32_t type;
    uint32_t count;
    bool normalized;
};

class VertexBufferLayout {
  public:
    VertexBufferLayout() : stride(0) {}
    ~VertexBufferLayout() {}

    /* Function:    push
       Description: Pushes new layout to list
       Parameters:  uint32_t - Number of elements describing VBO for VAO to understand
       Returns:     None 
    */
    void push(uint32_t count, uint16_t type) {
        elements.push_back({type, count, true});

        switch(type) {
           case GL_FLOAT:
             stride += sizeof(GLfloat) * count;
             break;
           case GL_UNSIGNED_BYTE:
             stride += sizeof(GLuint) * count;
             break;
        }
        
    }

    /* Function:    getElements
       Description: Returns list of elements for VAO
       Parameters:  None
       Returns:     vector - List of element data describing VBO
    */
    inline const std::vector<VertexBufferElement> getElements() const {return elements;}

    /* Function:    getStride
       Description: Returns the stride of VBO
       Parameters:  None
       Returns:     uint32_t - Stride of VBO 
    */
    inline uint32_t getStride() const {return stride;}
  private:
    std::vector<VertexBufferElement> elements; 
    uint32_t stride;
};

#endif