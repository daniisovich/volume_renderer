#pragma once

#include <glad/glad.h>

#include <array>
#include <vector>


namespace dvr {
	namespace gl {

		class Texture2D {

		public:

			Texture2D(GLenum internal_format, const std::array<uint32_t, 2>& size);
			Texture2D(GLenum format, GLenum internal_format, const std::array<uint32_t, 2>& size, GLenum data_type, const std::vector<uint8_t>& data,
				const std::vector<std::pair<GLenum, GLenum>>& texture_params, bool mipmap = false, const std::array<float, 4>& border_color = { 0.0f, 0.0f, 0.0f, 0.0f });

			Texture2D() = delete;
			Texture2D(const Texture2D&) = delete;
			Texture2D& operator=(const Texture2D&) = delete;
			~Texture2D() = default;

			Texture2D(Texture2D&& other) noexcept;
			Texture2D& operator=(Texture2D&& other) noexcept;

			void activate(GLuint texture_unit) const;

			void changeSize(uint32_t width, uint32_t height);

			inline GLuint id() const { return m_id.value; }

		private:

			struct ID {
				ID() { glCreateTextures(GL_TEXTURE_2D, 1, &value); }
				~ID() { release(); }
				void release() { glDeleteTextures(1, &value); value = 0; }
				uint32_t value{ 0 };
			} m_id;

		};

	}
}