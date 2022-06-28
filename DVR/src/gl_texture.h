#pragma once

#include <glad/glad.h>

#include <vector>


class glTexture2D {

public:

	glTexture2D(GLenum format, uint32_t width, uint32_t height, GLenum data_type);
	glTexture2D(GLenum format, GLenum internal_format, uint32_t width, uint32_t height, GLenum data_type, const std::vector<char>& data,
		const std::vector<std::pair<GLenum, GLenum>>& texture_params, bool mipmap = false, const float* border_color = nullptr);

	glTexture2D() = delete;
	glTexture2D(const glTexture2D&) = delete;
	glTexture2D& operator=(const glTexture2D&) = delete;
	~glTexture2D() = default;
	
	glTexture2D(glTexture2D&& other) noexcept;
	glTexture2D& operator=(glTexture2D&& other) noexcept;

	void activate(GLuint texture_unit) const;

	inline GLuint id() const { return m_id.value; }

private:

	inline void bind() const { glBindTexture(GL_TEXTURE_2D, m_id.value); }
	inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

	struct ID {
		ID() { glGenTextures(1, &value); }
		~ID() { release(); }
		void release() { glDeleteTextures(1, &value); value = 0; }
		uint32_t value;
	} m_id;

};