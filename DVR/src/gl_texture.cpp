#include "gl_texture.h"


glTexture2D::glTexture2D(GLenum format, uint32_t width, uint32_t height, GLenum data_type) : m_id{} {

	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, data_type, nullptr);

	unbind();

}

glTexture2D::glTexture2D(GLenum format, GLenum internal_format, uint32_t width, uint32_t height, GLenum data_type, const std::vector<char>& data,
	const std::vector<std::pair<GLenum, GLenum>>& texture_params, bool mipmap, const float* border_color) : m_id{} {
	
	bind();

	for (const auto& [key, value] : texture_params) {
		glTexParameteri(GL_TEXTURE_2D, key, value);
	}
	if (border_color)
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, data_type, data.data());
	if (mipmap)
		glGenerateMipmap(GL_TEXTURE_2D);

	unbind();
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