#pragma once

#include "window.hpp"

const std::int32_t WINDOW_WIDTH = 800;
const std::int32_t WINDOW_HEIGHT = 600;
const std::string_view WINDOW_TITLE = "Block Craft 3D";

class Application {
public:
  void run() noexcept;

private:
  Window m_Window{WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE};
  bool m_ShowDebugMenu{false};
};
