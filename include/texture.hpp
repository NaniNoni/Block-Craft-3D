#pragma once

#include <filesystem>

class Texture {
public:
  explicit Texture(const std::filesystem::path &path) noexcept;
  void bind() const noexcept;
  void unbind() const noexcept;

  [[nodiscard]] std::int32_t getWidth() const noexcept { return m_Width; }
  [[nodiscard]] std::int32_t getHeight() const noexcept { return m_Height; }

private:
  std::uint32_t m_ID;
  const std::filesystem::path m_Path;

  std::int32_t m_Width, m_Height, m_Channels;
};
