#pragma once

// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <cstdint>
#include <string_view>

class Window {
public:
  explicit Window(std::int32_t width, std::int32_t height,
                  std::string_view title) noexcept;

  ~Window() noexcept;
  inline bool shouldClose() const noexcept {
    return glfwWindowShouldClose(m_Window);
  };
  inline void pollEvents() const noexcept { glfwPollEvents(); }
  inline void swapBuffers() const noexcept { glfwSwapBuffers(m_Window); }

private:
  GLFWwindow *m_Window{nullptr};

  static void framebufferSizeCallback(GLFWwindow *window, std::int32_t width,
                                      std::int32_t height);
};
