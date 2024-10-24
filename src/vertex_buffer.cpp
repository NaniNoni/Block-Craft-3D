#include "vertex_buffer.hpp"
#include "window.hpp"

/// Creates an OpenGL vertex buffer object.
/// The VBO is NOT unbound once filled with data.
VertexBuffer::VertexBuffer(const float *data, std::size_t size) noexcept {
  glGenBuffers(1, &m_ID);
  glBindBuffer(GL_ARRAY_BUFFER, m_ID);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::bind() const noexcept {
  glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

/// Binds GL_ARRAY_BUFFER to 0
void VertexBuffer::unbind() const noexcept { glBindBuffer(GL_ARRAY_BUFFER, 0); }
