#include "gl_program.h"

#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <fstream>
#include <sstream>


void linkStatus(GLuint program_id);


glProgram::glProgram() : m_id{ glCreateProgram() } {}

glProgram::glProgram(glProgram&& other) noexcept : m_id{ other.m_id } {
	other.m_id = 0;
}

glProgram::~glProgram() {
	glDeleteProgram(m_id);
}

void glProgram::load(const std::vector<ShaderInfo>& shader_infos) const {
	
	std::vector<glShader> shaders(shader_infos.size());
	for (int i{ 0 }; i < shaders.size(); ++i) {
		shaders[i].load(shader_infos[i]);
		glAttachShader(m_id, shaders[i].id());
	}

	glLinkProgram(m_id);
	linkStatus(m_id);	

}

void glProgram::setUniform(const char* name, GLint value) const {
	GLint location{ glGetUniformLocation(m_id, name) };
	setUniform(location, value);
}

void glProgram::setUniform(const char* name, const glm::mat4& matrix) const {
	GLint location{ glGetUniformLocation(m_id, name) };
	setUniform(location, matrix);
}

void glProgram::setUniform(GLint location, GLint value) const {
	glUniform1i(location, value);
}

void glProgram::setUniform(GLint location, const glm::mat4& matrix) const {
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
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