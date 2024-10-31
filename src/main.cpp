#include "application.hpp"

#include <spdlog/spdlog.h>

int main() {
  spdlog::set_level(spdlog::level::debug);

  Application app;
  app.run();
}
