#include "vertexBuffer.h"

VertexBuffer::VertexBuffer(const void *data, uint32_t size) {
  GLCall(glGenBuffers(1, &bufID));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufID));
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
  GLCall(glDeleteBuffers(1, &bufID));
}

void VertexBuffer::bind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufID));
}

void VertexBuffer::unbind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}