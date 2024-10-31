#include "index_buffer.hpp"

#include <glad/gl.h>

/// Creates an OpenGL vertex buffer object.
/// The VBO is NOT unbound once filled with data.
IndexBuffer::IndexBuffer(const uint32_t *data, std::size_t size) noexcept {
  glGenBuffers(1, &m_ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  unbind();
}

void IndexBuffer::bind() const noexcept {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

/// Binds GL_ARRAY_BUFFER to 0
void IndexBuffer::unbind() const noexcept {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
