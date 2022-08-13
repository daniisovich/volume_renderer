#pragma once

#include <glad/glad.h>


struct ShaderInfo {
	GLenum type;
	std::string_view path;
};

namespace dvr {
	namespace gl {

		class Shader {

		public:

			Shader(ShaderInfo info);

			Shader() = delete;
			Shader(const Shader&) = delete;
			Shader& operator=(const Shader&) = delete;
			~Shader() = default;

			Shader(Shader&& other) noexcept;
			Shader& operator=(Shader&& other) noexcept;

			inline GLuint id() const { return m_id.value; }

		private:

			struct ID {
				ID(GLenum type) : value{ glCreateShader(type) } {}
				~ID() { release(); }
				void release() { glDeleteShader(value); value = 0; }
				GLuint value{ 0 };
			} m_id;
		};

	}
}
