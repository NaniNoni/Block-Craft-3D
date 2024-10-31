#include "texture.hpp"

#include <glad/gl.h>
#include <spdlog/spdlog.h>
#include <stb_image.h>

Texture::Texture(const std::filesystem::path &path) noexcept : m_Path(path) {
  spdlog::debug("Loading texture {}", path.string());

  if (!std::filesystem::exists(path)) {
    spdlog::error("Cannot load texture. File {} doesn't exist", path.string());
  }

  stbi_set_flip_vertically_on_load(true);
  std::uint8_t *data =
      stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);
  if (!data) {
    spdlog::error("stbi_load failed on file {}", path.string());
  }

  glGenTextures(1, &m_ID);
  bind();

  // set the texture wrapping/filtering options (on the currently bound texture
  // object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
  unbind();
}

void Texture::bind() const noexcept { glBindTexture(GL_TEXTURE_2D, m_ID); }
void Texture::unbind() const noexcept { glBindTexture(GL_TEXTURE_2D, 0); }
