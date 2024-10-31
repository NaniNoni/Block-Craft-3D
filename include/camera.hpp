#pragma once

#include <glm/glm.hpp>

class Camera {
public:
  explicit Camera(const glm::vec3 position, float speed) noexcept
      : position(position), m_Speed(speed) {}

  [[nodiscard]] glm::mat4 calculateViewMatrix() const noexcept;

  glm::vec3 position{0.0f, 0.0f, 3.0f};

  [[nodiscard]] float getSpeed() const noexcept { return m_Speed; }
  void setSpeed(float speed) noexcept { m_Speed = speed; }
  [[nodiscard]] const glm::vec3 &getFront() const noexcept { return m_Front; }
  [[nodiscard]] const glm::vec3 &getUp() const noexcept { return m_Up; }

private:
  float m_Speed{};
  const glm::vec3 m_Front{0.0f, 0.0f, -1.0f};
  const glm::vec3 m_Up{0.0, 1.0f, 0.0f};
};
