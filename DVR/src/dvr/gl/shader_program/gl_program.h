#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "dvr/gl/shader_program/gl_shader.h"


struct AttributeInfo {
	GLint location;
	GLsizei count;
	GLenum type;
};

struct UniformInfo {
	GLint location;
	GLsizei count;
	GLenum type;
};


namespace dvr::gl {

	class Program {

	public:

		Program(const std::vector<ShaderInfo>& shader_infos);

		Program() = delete;
		Program(const Program&) = delete;
		Program& operator=(const Program&) = delete;
		~Program() = default;

		Program(Program&& other) noexcept;
		Program& operator=(Program&& other) noexcept;

		inline void enable() const { glUseProgram(m_id.value); }
		inline void disable() const { glUseProgram(0); }
		inline void validate() const { glValidateProgram(m_id.value); }

		void setUniform(const char* name, GLint value);
		void setUniform(const char* name, GLfloat value);
		void setUniform(const char* name, const glm::mat4& matrix);

		void setUniform(GLint location, GLint value) const;
		void setUniform(GLint location, GLfloat value) const;
		void setUniform(GLint location, const glm::mat4& matrix) const;

		inline GLint attributeLocation(const std::string& name) { return m_attributes[name].location; }

	private:

		void retrieveAttributes();
		void retrieveUniforms();
		GLint retrieveValue(GLenum type) const;

		struct ID {
			ID() : value{ glCreateProgram() } {}
			~ID() { release(); }
			void release() { glDeleteProgram(value); value = 0; }
			GLuint value{ 0 };
		} m_id;

		std::unordered_map<std::string, AttributeInfo> m_attributes{};
		std::unordered_map<std::string, UniformInfo> m_uniforms{};

	};

}
