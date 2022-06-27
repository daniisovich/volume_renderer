#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "gl_shader.h"


class glProgram {

public:

	glProgram(const glProgram&) = delete;
	glProgram& operator=(const glProgram&) = delete;

	glProgram();
	glProgram(glProgram&& other) noexcept;
	~glProgram();

	void load(const std::vector<ShaderInfo>& shaders) const;

	inline void enable() const { glUseProgram(m_id); }
	inline void disable() const { glUseProgram(0); }

	inline GLint attributeLocation(const std::string& name) const { return glGetAttribLocation(m_id, name.c_str()); }
	inline GLint uniformLocation(const std::string& name) const { return glGetUniformLocation(m_id, name.c_str()); }


	void setUniform(const char* name, GLint value) const;
	void setUniform(const char* name, const glm::mat4& matrix) const;
	
	void setUniform(GLint location, GLint value) const;
	void setUniform(GLint location, const glm::mat4& matrix) const;

private:

	GLuint m_id{ 0 };

};