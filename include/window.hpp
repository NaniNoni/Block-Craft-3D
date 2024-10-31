#pragma once

// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <cstdint>
#include <functional>
#include <string_view>

class Window {
public:
  explicit Window(std::int32_t width, std::int32_t height,
                  std::string_view title) noexcept;

  ~Window() noexcept;
  [[nodiscard]] bool shouldClose() const noexcept {
    return glfwWindowShouldClose(m_Window);
  };
  void pollEvents() const noexcept;
  void swapBuffers() const noexcept { glfwSwapBuffers(m_Window); }
  /// This function starts a new ImGui frame
  /// Must be called before any rendering takes place
  void newFrame() const noexcept;

  void toggleVSync() const noexcept;
  /// Used to pass the pointer to the internal vertical sync tracker to ImGui
  /// for the debug menu.
  bool *getVSyncPtr() noexcept { return &m_VerticalSync; }

  void setKeyCallback(std::function<void(std::int32_t, std::int32_t,
                                         std::int32_t, std::int32_t)>
                          callback) const noexcept;

private:
  GLFWwindow *m_Window{nullptr};
  bool m_VerticalSync{true};

  static void keyCallback(GLFWwindow *window, std::int32_t key,
                          std::int32_t scancode, std::int32_t action,
                          std::int32_t mods) noexcept;
  static void glfwErrorCallback(std::int32_t errorCode,
                                const char *message) noexcept;
  static void framebufferSizeCallback(GLFWwindow *window, std::int32_t width,
                                      std::int32_t height) noexcept;
};
