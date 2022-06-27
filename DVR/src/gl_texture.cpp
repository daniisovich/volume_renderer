#include "gl_texture.h"


glTexture::glTexture(GLenum type) : m_type{ type } {
	glGenTextures(1, &m_id);
}

glTexture::glTexture(glTexture&& other) noexcept : m_id{ other.m_id }, m_type { other.m_type } {
	other.m_id = 0;
}

glTexture::~glTexture() {
	glDeleteTextures(1, &m_id);
}

void glTexture::activate(GLuint texture_unit) const {
	glActiveTexture(GL_TEXTURE0 + texture_unit);
	bind();
}

void glTexture::attach(GLenum format, GLenum internal_format, uint32_t width, uint32_t height, GLenum data_type) const {

	bind();
	glTexImage2D(m_type, 0, internal_format, width, height, 0, format, data_type, nullptr);
	glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unbind();

}

void glTexture::attach(GLenum format, GLenum internal_format, uint32_t width, uint32_t height, GLenum data_type, const std::vector<char>& data,
						const std::unordered_map<GLenum, GLenum>& texture_params, bool mipmap, const float* border_color) const {

	bind();

	for (const auto& [key, value] : texture_params) {
		glTexParameteri(m_type, key, value);
	}
	if (border_color)
		glTexParameterfv(m_type, GL_TEXTURE_BORDER_COLOR, border_color);

	glTexImage2D(m_type, 0, internal_format, width, height, 0, format, data_type, data.data());
	if (mipmap) 
		glGenerateMipmap(m_type);

	unbind();

}