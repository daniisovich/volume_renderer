#include "precompiled/pch.h"
#pragma hdrstop

#include "gl_program.h"

#include <glm/gtc/type_ptr.hpp>


static void linkStatus(GLuint program_id);


namespace dvr::gl {

	void Program::retrieveAttributes() {

		GLint attribute_count{ retrieveValue(GL_ACTIVE_ATTRIBUTES) };
		if (attribute_count) {

			GLint max_name_len{ retrieveValue(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH) };

			auto attribute_name{ std::make_unique<char[]>(max_name_len) };
			GLsizei length{ 0 }, count{ 0 };
			GLenum type{ GL_NONE };

			for (GLint i{ 0 }; i < attribute_count; ++i) {
				glGetActiveAttrib(m_id.value, i, max_name_len, &length, &count, &type, attribute_name.get());
				AttributeInfo info{ glGetAttribLocation(m_id.value, attribute_name.get()), count, type };

				m_attributes.emplace(std::string(attribute_name.get(), length), info);
			}

		}

	}

	void Program::retrieveUniforms() {

		GLint uniform_count{ retrieveValue(GL_ACTIVE_UNIFORMS) };
		if (uniform_count) {

			GLint max_name_len{ retrieveValue(GL_ACTIVE_UNIFORM_MAX_LENGTH) };

			auto uniform_name{ std::make_unique<char[]>(max_name_len) };
			GLsizei length{ 0 }, count{ 0 };
			GLenum type{ GL_NONE };

			for (GLint i{ 0 }; i < uniform_count; ++i) {
				glGetActiveUniform(m_id.value, i, max_name_len, &length, &count, &type, uniform_name.get());
				UniformInfo info{ glGetUniformLocation(m_id.value, uniform_name.get()), count, type };

				m_uniforms.emplace(std::string(uniform_name.get(), length), info);
			}

		}

	}

	GLint Program::retrieveValue(GLenum type) const {
		GLint value;
		glGetProgramiv(m_id.value, type, &value);
		return value;
	}

	Program::Program(const std::vector<ShaderInfo>& shader_infos) : m_id{} {

		std::vector<Shader> shaders;
		shaders.reserve(shader_infos.size());

		for (const auto& info : shader_infos)
			shaders.emplace_back(info);

		for (const auto& shader : shaders)
			glAttachShader(m_id.value, shader.id());

		glLinkProgram(m_id.value);
		for (const auto& shader : shaders)
			glDetachShader(m_id.value, shader.id());

		linkStatus(m_id.value);

		retrieveAttributes();
		retrieveUniforms();

	}

	Program::Program(Program&& other) noexcept : m_id{ other.m_id }, m_uniforms{ other.m_uniforms } {
		other.m_id.value = 0;
		other.m_uniforms.clear();
	}

	Program& Program::operator=(Program&& other) noexcept {

		if (this != &other) {
			m_id.release();
			m_uniforms.clear();
			std::swap(m_id, other.m_id);
			std::swap(m_uniforms, other.m_uniforms);
		}
		return *this;

	}

	void Program::setUniform(const char* name, GLint value) {
		setUniform(m_uniforms[name].location, value);
	}

	void Program::setUniform(const char* name, GLfloat value) {
		setUniform(m_uniforms[name].location, value);
	}

	void Program::setUniform(const char* name, const glm::mat4& matrix) {
		setUniform(m_uniforms[name].location, matrix);
	}

	void Program::setUniform(GLint location, GLint value) const {
		glProgramUniform1i(m_id.value, location, value);
	}

	void Program::setUniform(GLint location, GLfloat value) const {
		glProgramUniform1f(m_id.value, location, value);
	}

	void Program::setUniform(GLint location, const glm::mat4& matrix) const {
		glProgramUniformMatrix4fv(m_id.value, location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}


void linkStatus(GLuint program_id) {

	GLint success{ 0 };
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (!success) {
		GLint log_length;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

		std::string log(log_length - 1, ' ');
		glGetProgramInfoLog(program_id, log_length, nullptr, log.data());

		throw std::runtime_error("Error::Program::ID" + std::to_string(program_id) + "::LinkingFailed\n" + log);
	}
}