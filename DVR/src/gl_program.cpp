#include "gl_program.h"

#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <fstream>
#include <sstream>


void linkStatus(GLuint program_id);


glProgram::glProgram(const std::vector<ShaderInfo>& shader_infos) : m_id{} {

	std::vector<glShader> shaders;
	shaders.reserve(shader_infos.size());

	for (const auto& info : shader_infos)
		shaders.push_back(std::move(glShader(info)));

	for (const auto& shader : shaders)
		glAttachShader(m_id.value, shader.id());

	glLinkProgram(m_id.value);
	linkStatus(m_id.value);

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

glProgram::glProgram(glProgram&& other) noexcept : m_id{ other.m_id } {
	other.m_id.value = 0;
}

glProgram& glProgram::operator=(glProgram&& other) noexcept {

	if (this != &other) {
		m_id.release();
		std::swap(m_id, other.m_id);
	}
	return *this;

}

void glProgram::setUniform(const char* name, GLint value) const {
	GLint location{ glGetUniformLocation(m_id.value, name)};
	setUniform(location, value);
}

void glProgram::setUniform(const char* name, const glm::mat4& matrix) const {
	GLint location{ glGetUniformLocation(m_id.value, name)};
	setUniform(location, matrix);
}

void glProgram::setUniform(GLint location, GLint value) const {
	glUniform1i(location, value);
}

void glProgram::setUniform(GLint location, const glm::mat4& matrix) const {
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}