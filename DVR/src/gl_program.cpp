#include "gl_program.h"

#include <stdexcept>
#include <fstream>
#include <sstream>


void linkStatus(GLuint program_id);


glProgram::glProgram() : m_id{ glCreateProgram() } {}

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