#pragma once

#include <glad/glad.h>

#include <vector>


class glTexture3D {

public:

	glTexture3D(GLenum internal_format, uint32_t width, uint32_t height);
	glTexture3D(GLenum format, uint32_t width, uint32_t height, uint32_t depth, GLenum data_type, const std::vector<char>& data,
		const std::vector<std::pair<GLenum, GLenum>>& texture_params, bool mipmap = false, const float* border_color = nullptr);

	glTexture3D() = delete;
	glTexture3D(const glTexture3D&) = delete;
	glTexture3D& operator=(const glTexture3D&) = delete;
	~glTexture3D() = default;

	glTexture3D(glTexture3D&& other) noexcept;
	glTexture3D& operator=(glTexture3D&& other) noexcept;

	void activate(GLuint texture_unit) const;

	inline GLuint id() const { return m_id.value; }

private:

	struct ID {
		ID() { glCreateTextures(GL_TEXTURE_3D, 1, &value); }
		~ID() { release(); }
		void release() { glDeleteTextures(1, &value); value = 0; }
		uint32_t value{ 0 };
	} m_id;

};