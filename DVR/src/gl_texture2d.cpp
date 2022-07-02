#include "gl_texture2d.h"


glTexture2D::glTexture2D(GLenum internal_format, const std::array<uint32_t, 2>& size) : m_id{} {

	glTextureParameteri(m_id.value, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_id.value, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(m_id.value, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_id.value, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureStorage2D(m_id.value, 1, internal_format, size[0], size[1]);

}

glTexture2D::glTexture2D(GLenum format, GLenum internal_format, const std::array<uint32_t, 2>& size, GLenum data_type, const std::vector<uint8_t>& data,
	const std::vector<std::pair<GLenum, GLenum>>& texture_params, bool mipmap, const std::array<float, 4>& border_color) : m_id{} {

	for (const auto& [key, value] : texture_params) {
		glTextureParameteri(m_id.value, key, value);
	}
	glTextureParameterfv(m_id.value, GL_TEXTURE_BORDER_COLOR, border_color.data());

	glTextureStorage2D(m_id.value, 1, internal_format, size[0], size[1]);
	glTextureSubImage2D(m_id.value, 0, 0, 0, size[0], size[1], format, data_type, data.data());
	if (mipmap)
		glGenerateMipmap(m_id.value);

}

glTexture2D::glTexture2D(glTexture2D&& other) noexcept : m_id{ other.m_id } {
	other.m_id.value = 0;
}

glTexture2D& glTexture2D::operator=(glTexture2D&& other) noexcept {

	if (this != &other) {
		m_id.release();
		std::swap(m_id, other.m_id);
	}
	return *this;

}

void glTexture2D::activate(GLuint texture_unit) const {
	glBindTextureUnit(texture_unit, m_id.value);
}