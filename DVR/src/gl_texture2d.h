#pragma once

#include <glad/glad.h>

#include <array>
#include <vector>


class glTexture2D {

public:

	glTexture2D(GLenum internal_format, const std::array<uint32_t, 2>& size);
	glTexture2D(GLenum format, GLenum internal_format, const std::array<uint32_t, 2>& size, GLenum data_type, const std::vector<uint8_t>& data,
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

	struct ID {
		ID() {glCreateTextures(GL_TEXTURE_2D, 1, &value); }
		~ID() { release(); }
		void release() { glDeleteTextures(1, &value); value = 0; }
		uint32_t value{ 0 };
	} m_id;

};