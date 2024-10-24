#include "shader_program.hpp"
#include "window.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

const std::string_view debugVertexShaderSource =
    R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main() {
  gl_Position = vec4(aPos.xyz, 1.0);
}
)";

const std::string_view debugFragmentShaderSource =
    R"(
#version 330 core
out vec4 fragColor;

void main() {
    fragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
}
)";

static std::string readFile(const std::filesystem::path &path) {
  std::ifstream fileStream{path};

  if (!fileStream.is_open()) {
    throw std::runtime_error("Failed to open file: " + path.string());
  }

  std::ostringstream contents;
  contents << fileStream.rdbuf();

  return contents.str();
}

ShaderProgram::ShaderProgram(
    const std::filesystem::path &vertexShaderPath,
    const std::filesystem::path &fragmentShaderPath) noexcept {
  std::string vertexShaderSource;
  std::string fragmentShaderSource;

  try {
    vertexShaderSource = readFile(vertexShaderPath);
    fragmentShaderSource = readFile(fragmentShaderPath);
  } catch (const std::exception &e) {
    std::cout << e.what();
    std::exit(EXIT_FAILURE);
  }

  std::uint32_t vertexShader =
      createShader(GL_VERTEX_SHADER, vertexShaderSource);
  std::uint32_t fragmentShader =
      createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

  m_ID = createProgram(vertexShader, fragmentShader);
  use();
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

/// Creates an OpenGL shader program with a vertex and fragment shader.
/// It creates the vertex and fragment shaders themselves and deletes them
/// when they're no longer necessary. Uses the very simple, default "debug"
/// shaders.
ShaderProgram::ShaderProgram() noexcept {
  std::uint32_t vertexShader =
      createShader(GL_VERTEX_SHADER, debugVertexShaderSource);
  std::uint32_t fragmentShader =
      createShader(GL_FRAGMENT_SHADER, debugFragmentShaderSource);

  m_ID = createProgram(vertexShader, fragmentShader);
  use();
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void ShaderProgram::use() const noexcept { glUseProgram(m_ID); }

std::uint32_t
ShaderProgram::createShader(std::uint32_t shaderType,
                            std::string_view shaderSource) noexcept {
  std::uint32_t id;
  id = glCreateShader(shaderType);
  const char *data = shaderSource.data();
  glShaderSource(id, 1, &data, nullptr);
  glCompileShader(id);

  std::int32_t success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success) {
    std::int32_t logLength;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
    char *infoLog = new char[logLength];

    glGetShaderInfoLog(id, logLength, nullptr, infoLog);
    std::cout << "Failed to compile" << shaderType << " shader." << infoLog
              << '\n';

    delete[] infoLog;
  }

  return id;
}

std::uint32_t
ShaderProgram::createProgram(std::uint32_t vertexShader,
                             std::uint32_t fragmentShader) noexcept {
  std::uint32_t ID;
  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);

  std::int32_t success;
  glGetShaderiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    std::int32_t logLength;
    glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logLength);
    char *infoLog = new char[logLength];

    glGetShaderInfoLog(ID, logLength, nullptr, infoLog);
    std::cout << "Failed to link shader program." << infoLog << '\n';

    delete[] infoLog;
  }

  return ID;
}
