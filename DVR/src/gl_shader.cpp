#include "gl_shader.h"
#include <iostream>
#include <fstream>
#include <sstream>


std::string loadSource(std::string_view path);
void compileStatus(GLuint shader_id);
std::string shaderType(GLuint shader_id);


glShader::glShader(ShaderInfo info) : m_id{ info.type } {

	const std::string source_str{ loadSource(info.path) };
	const char* source{ source_str.c_str() };

	glShaderSource(m_id.value, 1, &source, nullptr);

	glCompileShader(m_id.value);
	compileStatus(m_id.value);

}

glShader::glShader(glShader&& other) noexcept : m_id{ other.m_id } {
	other.m_id.value = 0;
}

glShader& glShader::operator=(glShader&& other) noexcept {

	if (this != &other) {
		m_id.release();
		std::swap(m_id, other.m_id);
	}
	return *this;

}

std::string loadSource(std::string_view path) {

	std::ifstream file{ path.data() };
	if (!file) {
		std::string path_str{ path };
		throw std::runtime_error("Failed to open file " + path_str);
	}

	std::stringstream str_stream;
	str_stream << file.rdbuf();

	return str_stream.str();

}

void compileStatus(GLuint shader_id) {

	GLint success{ 0 };
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLint log_length{ 0 };
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

		std::string log(log_length - 1, ' ');
		glGetShaderInfoLog(shader_id, log_length, nullptr, log.data());

		std::string type{ shaderType(shader_id) };
		throw std::runtime_error("Error::Shader::" + type + "::CompilationFailed\n" + log);
	}

}

std::string shaderType(GLuint shader_id) {
	
	GLint shader_type{ 0 };
	glGetShaderiv(shader_id, GL_SHADER_TYPE, &shader_type);
	
	switch (shader_type) {
	case GL_VERTEX_SHADER:			return "Vertex";
	case GL_FRAGMENT_SHADER:		return "Fragment";
	case GL_GEOMETRY_SHADER:		return "Geometry";
	case GL_TESS_CONTROL_SHADER:	return "Tessc";
	case GL_TESS_EVALUATION_SHADER:	return "Tesse";
	case GL_COMPUTE_SHADER:			return "Compute";
	default:						return "Unknown";
	}

}
