#include "application.hpp"

#include "imgui_impl_opengl3.h"
#include "index_buffer.hpp"
#include "shader_program.hpp"
#include "spdlog/spdlog.h"
#include "texture.hpp"
#include "vertex_buffer.hpp"
#include "window.hpp"

#include <imgui.h>

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

  float vertices[] = {
      // positions        // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // top left
  };

  // Put vertices in VRAM
  VertexBuffer VBO{vertices, sizeof(vertices)};
  VBO.bind();
  IndexBuffer IBO{indices, sizeof(indices)};
  IBO.bind();

  Texture textureAtlas{"../assets/Textures-16.png"};
  textureAtlas.bind();

  // OpenGL guarantees there are always at least 16 4-component vertex
  // attributes available, but some hardware may allow for more which you can
  // retrieve by querying GL_MAX_VERTEX_ATTRIBS.
  // Set up vertex attrib pointers
  const std::size_t stride = 5 * sizeof(float);
  std::size_t ptr = 0;
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride,
                        reinterpret_cast<void *>(ptr));
  glEnableVertexAttribArray(0);
  ptr += 3 * sizeof(float);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride,
                        reinterpret_cast<void *>(ptr));
  glEnableVertexAttribArray(1);

  ShaderProgram shaderProgram{"../shaders/vertex.glsl",
                              "../shaders/fragment.glsl"};
  shaderProgram.bind();

  shaderProgram.set("ligma_value", 0.5f);

  m_Window.setKeyCallback([&](std::int32_t key, std::int32_t scancode,
                              std::int32_t action, std::int32_t mods) {
    if (action != GLFW_PRESS) {
      return;
    }

    switch (key) {
    case GLFW_KEY_F3: {
      m_ShowDebugMenu = !m_ShowDebugMenu;
      break;
    }
    }
  });

  while (!m_Window.shouldClose()) {
    m_Window.pollEvents();
    m_Window.newFrame();

    if (m_ShowDebugMenu) {
      ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
      ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
      ImGui::Begin("Debug Menu", nullptr,
                   ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);

      ImGui::LabelText("GL Vendor", "%s", glGetString(GL_VENDOR));
      ImGui::LabelText("GL Renderer", "%s", glGetString(GL_RENDERER));
      ImGui::LabelText("GL Version", "%s", glGetString(GL_VERSION));
      ImGui::LabelText("GLSL Version", "%s",
                       glGetString(GL_SHADING_LANGUAGE_VERSION));

      if (ImGui::Checkbox("Vertical Sync", m_Window.getVSyncPtr())) {
        spdlog::debug("Vsync toggle");
        m_Window.toggleVSync();
      }

      ImGui::End();
      ImGui::PopStyleVar();
    }

    ImGui::Render();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    m_Window.swapBuffers();
  }
}
