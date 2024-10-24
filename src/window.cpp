#include "window.hpp"
#include "GLFW/glfw3.h"

#include <cstdlib>
#include <iostream>

const std::int32_t WINDOW_WIDTH = 1920;
const std::int32_t WINDOW_HEIGHT = 1080;

Window::Window(std::int32_t width, std::int32_t height,
               std::string_view title) noexcept {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  m_Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL",
                              nullptr, nullptr);

  if (!m_Window) {
    std::cout << "Failed to create GLFW window\n";
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(m_Window);

  if (!gladLoadGL(glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD\n";
    exit(EXIT_FAILURE);
  }

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetFramebufferSizeCallback(m_Window, Window::framebufferSizeCallback);
}

Window::~Window() noexcept { glfwTerminate(); }

void Window::framebufferSizeCallback(GLFWwindow *window, std::int32_t width,
                                     std::int32_t height) {
  glViewport(0, 0, width, height);
}
