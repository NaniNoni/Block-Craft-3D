#pragma once

#include <cstdint>
#include <filesystem>
#include <string_view>

class ShaderProgram {
public:
  explicit ShaderProgram() noexcept;
  explicit ShaderProgram(
      const std::filesystem::path &vertexShaderPath,
      const std::filesystem::path &fragmentShaderPath) noexcept;
  void bind() const noexcept;
  void unbind() const noexcept;

  template <typename T> void set(std::string_view name, T value) const noexcept;

private:
  std::uint32_t m_ID{0};

  static std::uint32_t createShader(std::uint32_t shaderType,
                                    std::string_view shaderSource) noexcept;
  static std::uint32_t createProgram(std::uint32_t vertexShader,
                                     std::uint32_t fragmentShader) noexcept;
};
