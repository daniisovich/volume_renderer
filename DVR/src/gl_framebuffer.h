#pragma once

#include "gl_texture2d.h"


class glFramebuffer {

public:

	glFramebuffer(const glTexture2D& texture, uint32_t attachment, uint32_t mipmap_level);
	
	glFramebuffer() = delete;
	glFramebuffer(const glFramebuffer&) = delete;
	glFramebuffer& operator=(const glFramebuffer&) = delete;
	~glFramebuffer() = default;

	glFramebuffer(glFramebuffer&& other) noexcept;
	glFramebuffer& operator=(glFramebuffer&& other) noexcept;

	inline void bind() const { glBindFramebuffer(GL_FRAMEBUFFER, m_id.value); }
	inline void unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

private:

	struct ID {
		ID() { glCreateFramebuffers(1, &value); }
		~ID() { release(); }
		void release() { glDeleteFramebuffers(1, &value); value = 0; }
		uint32_t value;
	} m_id;
	
};