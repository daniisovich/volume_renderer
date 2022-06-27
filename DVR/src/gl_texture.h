#pragma once

#include <glad/glad.h>

#include <unordered_map>


class glTexture {

public:
	
	glTexture() = delete;
	glTexture(const glTexture&) = delete;
	glTexture& operator=(const glTexture&) = delete;

	glTexture(GLenum type);
	glTexture(glTexture&& other) noexcept;
	~glTexture();

	void attach(GLenum format, GLenum internal_format, uint32_t width, uint32_t height, GLenum data_type) const;
	void attach(GLenum format, GLenum internal_format, uint32_t width, uint32_t height, GLenum data_type, const std::vector<char>& data,
					const std::unordered_map<GLenum, GLenum>& texture_params, bool mipmap = false, const float* border_color = nullptr) const;

	inline GLuint id() const { return m_id; }
	inline GLenum type() const { return m_type; }

	void activate(GLuint texture_unit) const;

private:

	inline void bind() const { glBindTexture(m_type, m_id); }
	inline void unbind() const { glBindTexture(m_type, 0); }

	GLuint m_id{ 0 };
	GLenum m_type;

};