#include "camera.hpp"

#include <glm/ext.hpp>

glm::mat4 Camera::calculateViewMatrix() const noexcept {
  return glm::lookAt(position, position + m_Front, m_Up);
}
