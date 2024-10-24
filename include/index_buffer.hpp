#pragma once

#include <cstddef>
#include <cstdint>

class IndexBuffer {
public:
  explicit IndexBuffer(const std::uint32_t *data, std::size_t size) noexcept;

  void bind() const noexcept;
  void unbind() const noexcept;

private:
  std::uint32_t m_ID{0};
};
