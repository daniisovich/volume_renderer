#pragma once

#include <glad/glad.h>

#include <array>
#include <vector>


class glTexture3D {

public:

	glTexture3D(GLenum internal_format, const std::array<uint32_t, 3>& size);
	glTexture3D(GLenum format, GLenum internal_format, const std::array<uint32_t, 3>& size, GLenum data_type, const std::vector<uint8_t>& data,
		const std::vector<std::pair<GLenum, GLenum>>& texture_params, bool mipmap = false, const std::array<float, 4>& border_color = { 0.0f, 0.0f, 0.0f, 0.0f });

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