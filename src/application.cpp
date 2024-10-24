#include "application.hpp"
#include "index_buffer.hpp"
#include "shader_program.hpp"
#include "vector.hpp"
#include "vertex_buffer.hpp"
#include <iostream>

float vertices[] = {
    0.5f,  0.5f,  0.0f, // top right
    0.5f,  -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f,  0.0f  // top left
};

std::uint32_t indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

void Application::run() noexcept {
  // Render in wireframe mode
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  std::uint32_t VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Put vertices in VRAM
  VertexBuffer VBO{vertices, sizeof(vertices)};
  IndexBuffer IBO{indices, sizeof(indices)};

  // OpenGL guarantees there are always at least 16 4-component vertex
  // attributes available, but some hardware may allow for more which you can
  // retrieve by querying GL_MAX_VERTEX_ATTRIBS.
  // Set up vertex attrib pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
  glEnableVertexAttribArray(0);

  ShaderProgram shaderProgram{"../shaders/vertex.glsl",
                              "../shaders/fragment.glsl"};

  Vector3<float> playerPos = Vector3(0.0f, 0.0f, 0.0f);
  Vector3<float> test = Vector3(5.0f, 0.0f, 0.0f);
  Vector3 temp = playerPos + test;
  std::cout << temp.toString() << '\n';

  while (!m_Window.shouldClose()) {
    m_Window.swapBuffers();
    m_Window.pollEvents();

    shaderProgram.use();
    glBindVertexArray(VAO);
    IBO.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}
