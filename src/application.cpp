#include "application.hpp"

#include "imgui_impl_opengl3.h"
#include "index_buffer.hpp"
#include "shader_program.hpp"
#include "spdlog/spdlog.h"
#include "texture.hpp"
#include "vertex_buffer.hpp"
#include "window.hpp"

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <imgui.h>

std::uint32_t indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

void Application::run() noexcept {
  // Render in wireframe mode
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glEnable(GL_DEPTH_TEST);

  std::uint32_t VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // clang-format off
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
  // clang-format on

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

    case GLFW_KEY_W: {
      m_Camera.position += m_Camera.getFront() * m_Camera.getSpeed();
      break;
    }
    case GLFW_KEY_S: {
      m_Camera.position -= m_Camera.getFront() * m_Camera.getSpeed();
      break;
    }
    case GLFW_KEY_A: {
      m_Camera.position -=
          glm::normalize(glm::cross(m_Camera.getFront(), m_Camera.getUp())) *
          m_Camera.getSpeed();
      break;
    }
    case GLFW_KEY_D: {
      m_Camera.position +=
          glm::normalize(glm::cross(m_Camera.getFront(), m_Camera.getUp())) *
          m_Camera.getSpeed();
      break;
    }
    }
  });

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 view = glm::mat4(1.0f);
  // note that we're translating the scene in the reverse direction of where
  // we want to move
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  glm::mat4 projection;
  projection =
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

  shaderProgram.set("model", model);
  shaderProgram.set("view", view);
  shaderProgram.set("projection", projection);

  float deltaTime = 0.0f; // Time between current frame and last frame
  float lastFrame = 0.0f; // Time of last frame

  while (!m_Window.shouldClose()) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    m_Camera.setSpeed(2.5f * deltaTime);

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    m_Window.swapBuffers();
  }
}
