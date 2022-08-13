#include "precompiled/pch.h"
#pragma hdrstop

#include "gl_texture3d.h"


namespace dvr::gl {

	Texture3D::Texture3D(GLenum internal_format, const std::array<uint32_t, 3>& size) : m_id{} {

		glTextureParameteri(m_id.value, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_id.value, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureStorage3D(m_id.value, 1, internal_format, size[0], size[1], size[2]);

	}

	Texture3D::Texture3D(GLenum format, GLenum internal_format, const std::array<uint32_t, 3>& size, GLenum data_type, const std::vector<uint8_t>& data,
		const std::vector<std::pair<GLenum, GLenum>>& texture_params, bool mipmap, const std::array<float, 4>& border_color) : m_id{} {

		for (const auto& [key, value] : texture_params) {
			glTextureParameteri(m_id.value, key, value);
		}
		glTextureParameterfv(m_id.value, GL_TEXTURE_BORDER_COLOR, border_color.data());

		glTextureStorage3D(m_id.value, 1, internal_format, size[0], size[1], size[2]);
		glTextureSubImage3D(m_id.value, 0, 0, 0, 0, size[0], size[1], size[2], format, data_type, data.data());
		if (mipmap)
			glGenerateMipmap(m_id.value);

	}

	Texture3D::Texture3D(Texture3D&& other) noexcept : m_id{ other.m_id } {
		other.m_id.value = 0;
	}

	Texture3D& Texture3D::operator=(Texture3D&& other) noexcept {

		if (this != &other) {
			m_id.release();
			std::swap(m_id, other.m_id);
		}
		return *this;

	}

	void Texture3D::activate(GLuint texture_unit) const {
		glBindTextureUnit(texture_unit, m_id.value);
	}

}
