#include "gl_framebuffer.h"

#include <glad/glad.h>

#include <stdexcept>


glFramebuffer::glFramebuffer(const glTexture2D& texture, uint32_t attachment, uint32_t mipmap_level) : m_id{} {

	glNamedFramebufferTexture(m_id.value, GL_COLOR_ATTACHMENT0 + attachment, texture.id(), mipmap_level);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		throw std::runtime_error("Error::Framebuffer::NotComplete");
	}
	unbind();

}

glFramebuffer::glFramebuffer(glFramebuffer&& other) noexcept : m_id{ other.m_id } {
	other.m_id.value = 0;
}

glFramebuffer& glFramebuffer::operator=(glFramebuffer&& other) noexcept {

	if (this != &other) {
		m_id.release();
		std::swap(m_id, other.m_id);
	}
	return *this;

}