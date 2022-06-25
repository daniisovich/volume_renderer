#include "gl_framebuffer.h"

#include <glad/glad.h>

#include <stdexcept>


glFramebuffer::glFramebuffer() {
	glGenFramebuffers(1, &m_id);
}

glFramebuffer::glFramebuffer(glFramebuffer&& other) noexcept : m_id{ other.m_id } {
	other.m_id = 0;
}

glFramebuffer::~glFramebuffer() {
	glDeleteFramebuffers(1, &m_id);
}

void glFramebuffer::attach(const glTexture& texture, int attachment, int mipmap_level) const {

	bind();
	switch (texture.type()) {
	case GL_TEXTURE_1D: glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, GL_TEXTURE_1D, texture.id(), mipmap_level);		break;
	case GL_TEXTURE_2D: glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, GL_TEXTURE_2D, texture.id(), mipmap_level);		break;
	case GL_TEXTURE_3D: glFramebufferTexture3D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, GL_TEXTURE_3D, texture.id(), mipmap_level, 0);	break;
	default: throw std::runtime_error("Error::Framebuffer::UnsupportedType");
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		throw std::runtime_error("Error::Framebuffer::NotComplete");
	}
	unbind();

}