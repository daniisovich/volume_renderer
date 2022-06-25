#include "gl_texture.h"


glTexture::glTexture(GLenum type) : m_type{ type } {
	glGenTextures(1, &m_id);
}

glTexture::glTexture(glTexture&& other) : m_id{ other.m_id }, m_type { other.m_type } {
	other.m_id = 0;
}

glTexture::~glTexture() {
	glDeleteTextures(1, &m_id);
}

void glTexture::attach(GLenum format, GLenum internal_format, int width, int height, GLenum data_type) {

	bind();
	glTexImage2D(m_type, 0, internal_format, width, height, 0, format, data_type, nullptr);
	glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unbind();

}