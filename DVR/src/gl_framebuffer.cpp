#include "gl_framebuffer.h"

#include <glad/glad.h>

#include <stdexcept>


glFramebuffer::glFramebuffer(GLenum format, const std::array<uint32_t, 2>& size, uint32_t attachment, uint32_t mipmap_level) : m_id{}, m_attachment{ format, size } {
	glNamedFramebufferTexture(m_id.value, GL_COLOR_ATTACHMENT0 + attachment, m_attachment.id(), mipmap_level);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		throw std::runtime_error("Error::Framebuffer::NotComplete");
	}
}

glFramebuffer::glFramebuffer(glFramebuffer&& other) noexcept : m_id{ other.m_id }, m_attachment{ std::move(other.m_attachment) } {
	other.m_id.value = 0;
}

glFramebuffer& glFramebuffer::operator=(glFramebuffer&& other) noexcept {

	if (this != &other) {
		m_attachment = std::move(other.m_attachment);
		m_id.release();
		std::swap(m_id, other.m_id);
	}
	return *this;

}