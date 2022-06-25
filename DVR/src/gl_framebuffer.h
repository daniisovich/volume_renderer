#pragma once

#include "gl_texture.h"


class glFramebuffer {

public:

	glFramebuffer(const glFramebuffer&) = delete;
	glFramebuffer& operator=(const glFramebuffer&) = delete;

	glFramebuffer();
	glFramebuffer(glFramebuffer&& other) noexcept;
	~glFramebuffer();

	inline void bind() const { glBindFramebuffer(GL_FRAMEBUFFER, m_id); }
	inline void unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

	void attach(const glTexture& texture, int attachment, int mipmap_level) const;

private:

	unsigned int m_id;

};