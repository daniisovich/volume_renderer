#include "gl_texture3d.h"


glTexture3D::glTexture3D(GLenum internal_format, const std::array<uint32_t, 3>& size) : m_id{} {

	glTextureParameteri(m_id.value, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_id.value, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureStorage3D(m_id.value, 1, internal_format, size[0], size[1], size[2]);

}

glTexture3D::glTexture3D(GLenum format, GLenum internal_format, const std::array<uint32_t, 3>& size, GLenum data_type, const std::vector<uint8_t>& data,
	const std::vector<std::pair<GLenum, GLenum>>& texture_params, bool mipmap, const float* border_color) : m_id{} {

	for (const auto& [key, value] : texture_params) {
		glTextureParameteri(m_id.value, key, value);
	}
	if (border_color)
		glTextureParameterfv(m_id.value, GL_TEXTURE_BORDER_COLOR, border_color);

	glTextureStorage3D(m_id.value, 1, internal_format, size[0], size[1], size[2]);
	glTextureSubImage3D(m_id.value, 0, 0, 0, 0, size[0], size[1], size[2], format, data_type, data.data());
	if (mipmap)
		glGenerateMipmap(m_id.value);

}

glTexture3D::glTexture3D(glTexture3D&& other) noexcept : m_id{ other.m_id } {
	other.m_id.value = 0;
}

glTexture3D& glTexture3D::operator=(glTexture3D&& other) noexcept {

	if (this != &other) {
		m_id.release();
		std::swap(m_id, other.m_id);
	}
	return *this;

}

void glTexture3D::activate(GLuint texture_unit) const {
	glBindTextureUnit(texture_unit, m_id.value);
}