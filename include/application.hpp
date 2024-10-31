#pragma once

#include "camera.hpp"
#include "window.hpp"

const std::int32_t WINDOW_WIDTH = 800;
const std::int32_t WINDOW_HEIGHT = 600;
const std::string_view WINDOW_TITLE = "Block Craft 3D";

class Application {
public:
  void run() noexcept;

private:
  Window m_Window{WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE};
  Camera m_Camera{{0.0f, 0.0f, 3.0f}, 0.05f};
  bool m_ShowDebugMenu{false};
};
