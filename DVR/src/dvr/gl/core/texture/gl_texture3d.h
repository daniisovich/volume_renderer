#pragma once

#include <glad/glad.h>

#include <array>
#include <vector>


namespace dvr {
	namespace gl {

		class Texture3D {

		public:

			Texture3D(GLenum internal_format, const std::array<uint32_t, 3>& size);
			Texture3D(GLenum format, GLenum internal_format, const std::array<uint32_t, 3>& size, GLenum data_type, const std::vector<uint8_t>& data,
				const std::vector<std::pair<GLenum, GLenum>>& texture_params, bool mipmap = false, const std::array<float, 4>& border_color = { 0.0f, 0.0f, 0.0f, 0.0f });

			Texture3D() = delete;
			Texture3D(const Texture3D&) = delete;
			Texture3D& operator=(const Texture3D&) = delete;
			~Texture3D() = default;

			Texture3D(Texture3D&& other) noexcept;
			Texture3D& operator=(Texture3D&& other) noexcept;

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

	}
}
