#include "gl_texture2d.h"


glTexture2D::glTexture2D(GLenum internal_format, uint32_t width, uint32_t height) : m_id{} {

	glTextureParameteri(m_id.value, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_id.value, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureStorage2D(m_id.value, 1, internal_format, width, height);

}

glTexture2D::glTexture2D(GLenum format, uint32_t width, uint32_t height, GLenum data_type, const std::vector<char>& data,
	const std::vector<std::pair<GLenum, GLenum>>& texture_params, bool mipmap, const float* border_color) : m_id{} {

	for (const auto& [key, value] : texture_params) {
		glTextureParameteri(m_id.value, key, value);
	}
	if (border_color)
		glTextureParameterfv(m_id.value, GL_TEXTURE_BORDER_COLOR, border_color);

	glTextureSubImage2D(m_id.value, 0, 0, 0, width, height, format, data_type, data.data());
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