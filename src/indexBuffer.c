#include "indexBuffer.h"

IndexBuffer::IndexBuffer(const uint32_t *data, uint32_t count) : count(count) {
  GLCall(glGenBuffers(1, &indexID));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &indexID);
}

void IndexBuffer::bind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID));
}

void IndexBuffer::unbind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}