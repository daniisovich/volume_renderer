#pragma once

#include <glad/glad.h>


class glTexture {

public:
	
	glTexture() = delete;
	glTexture(const glTexture&) = delete;
	glTexture& operator=(const glTexture&) = delete;

	glTexture(GLenum type);
	glTexture(glTexture&& other);
	~glTexture();

	void attach(GLenum format, GLenum internal_format, int width, int height, GLenum data_type);

	inline GLuint id() const { return m_id; }
	inline GLenum type() const { return m_type; }

	inline void bind() const { glBindTexture(m_type, m_id); }
	inline void unbind() const { glBindTexture(m_type, 0); }

private:

	GLuint m_id{ 0 };
	GLenum m_type;

};