#include "window.hpp"

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <functional>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <spdlog/spdlog.h>

Window::Window(std::int32_t width, std::int32_t height,
               std::string_view title) noexcept {
  glfwSetErrorCallback(Window::glfwErrorCallback);

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  m_Window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

  spdlog::debug("Creating window: {} ({}, {})", title, width, height);

  if (!m_Window) {
    spdlog::error("Failed to create GLFW window");
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(m_Window);

  if (!gladLoadGL(glfwGetProcAddress)) {
    spdlog::error("Failed to initialize GLAD");
    exit(EXIT_FAILURE);
  }

  // glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetFramebufferSizeCallback(m_Window, framebufferSizeCallback);

  spdlog::debug("Initializing ImGui: {}", ImGui::GetVersion());
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
  // TODO: support web
  ImGui_ImplOpenGL3_Init("#version 330");

  // FIXME: this is a hack to to "sorta" do DPI scaling
  // Figure out how to do this properly
  ImGui::GetIO().FontGlobalScale = 2;
}

void Window::setKeyCallback(
    std::function<void(std::int32_t, std::int32_t, std::int32_t, std::int32_t)>
        callback) const noexcept {
  static auto keyCallback = std::move(callback);

  glfwSetKeyCallback(m_Window, [](GLFWwindow *window, std::int32_t key,
                                  std::int32_t scancode, std::int32_t action,
                                  std::int32_t mods) {
    keyCallback(key, scancode, action, mods);
  });
}

void Window::pollEvents() const noexcept {
  glfwPollEvents();
  // FIXME: figure out if this is equivalent to the ImGui example
  // https://github.com/ocornut/imgui/blob/master/examples/example_glfw_opengl3/main.cpp
  if (glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED) != 0) {
    ImGui_ImplGlfw_Sleep(10);
    return;
  }
}

void Window::newFrame() const noexcept {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

Window::~Window() noexcept {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();
}

void Window::toggleVSync() const noexcept {
  spdlog::debug("Vertical sync toggled: {}",
                m_VerticalSync == true ? "on" : "off");
  glfwSwapInterval(m_VerticalSync);
}
void Window::glfwErrorCallback(std::int32_t errorCode,
                               const char *message) noexcept {
  spdlog::error("GLFW Error. Code: {}. Message: {}", errorCode, message);
}

void Window::framebufferSizeCallback(GLFWwindow *window, std::int32_t width,
                                     std::int32_t height) noexcept {
  glViewport(0, 0, width, height);
}
