#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "gl_shader.h"


class glProgram {

public:

	glProgram() = delete;
	glProgram(const glProgram&) = delete;
	glProgram& operator=(const glProgram&) = delete;
	~glProgram() = default;

	glProgram(const std::vector<ShaderInfo>& shader_infos);

	glProgram(glProgram&& other) noexcept;

	inline void enable() const { glUseProgram(m_id.value); }
	inline void disable() const { glUseProgram(0); }

	inline GLint attributeLocation(const std::string& name) const { return glGetAttribLocation(m_id.value, name.c_str()); }
	inline GLint uniformLocation(const std::string& name) const { return glGetUniformLocation(m_id.value, name.c_str()); }


	void setUniform(const char* name, GLint value) const;
	void setUniform(const char* name, const glm::mat4& matrix) const;
	
	void setUniform(GLint location, GLint value) const;
	void setUniform(GLint location, const glm::mat4& matrix) const;

private:

	struct ID {
		ID() : value{ glCreateProgram() } {}
		~ID() { glDeleteProgram(value); }
		GLuint value{ 0 };
	} m_id;

};