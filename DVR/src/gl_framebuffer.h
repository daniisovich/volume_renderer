#pragma once

#include "gl_texture2d.h"


class glFramebuffer {

public:

	glFramebuffer(GLenum format, const std::array<uint32_t, 2>& size, uint32_t attachment, uint32_t mipmap_level);
	
	glFramebuffer() = delete;
	glFramebuffer(const glFramebuffer&) = delete;
	glFramebuffer& operator=(const glFramebuffer&) = delete;
	~glFramebuffer() = default;

	glFramebuffer(glFramebuffer&& other) noexcept;
	glFramebuffer& operator=(glFramebuffer&& other) noexcept;

	inline void activateTexture(GLuint texture_unit) const { m_attachment.activate(texture_unit); }
	inline void bind() const { glBindFramebuffer(GL_FRAMEBUFFER, m_id.value); }
	inline void unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

private:

	struct ID {
		ID() { glCreateFramebuffers(1, &value); }
		~ID() { release(); }
		void release() { glDeleteFramebuffers(1, &value); value = 0; }
		uint32_t value;
	} m_id;
	
	glTexture2D m_attachment;

};