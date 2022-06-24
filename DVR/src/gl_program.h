#pragma once

#include <glad/glad.h>

#include <string>
#include <vector>

#include "gl_shader.h"


class glProgram {

public:

	glProgram(const glProgram&) = delete;
	glProgram& operator=(const glProgram&) = delete;

	glProgram();
	~glProgram();

	void load(const std::vector<ShaderInfo>& shaders) const;

	inline void enable() const { glUseProgram(m_id); }
	inline void disable() const { glUseProgram(0); }

	inline GLuint attributeLocation(const std::string& name) const { return glGetAttribLocation(m_id, name.c_str()); }
	inline GLuint uniformLocation(const std::string& name) const { return glGetUniformLocation(m_id, name.c_str()); }

private:

	GLuint m_id;

};