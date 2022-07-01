#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <unordered_map>
#include <string>
#include <vector>

#include "gl_shader.h"


struct UniformInfo {
	GLint location;
	GLsizei count;
	GLenum type;
};


class glProgram {

public:

	glProgram(const std::vector<ShaderInfo>& shader_infos);

	glProgram() = delete;
	glProgram(const glProgram&) = delete;
	glProgram& operator=(const glProgram&) = delete;
	~glProgram() = default;

	glProgram(glProgram&& other) noexcept;
	glProgram& operator=(glProgram&& other) noexcept;

	inline void enable() const { glUseProgram(m_id.value); }
	inline void disable() const { glUseProgram(0); }
	inline void validate() const { glValidateProgram(m_id.value); }

	void setUniform(const char* name, GLint value);
	void setUniform(const char* name, const glm::mat4& matrix);

	void setUniform(GLint location, GLint value) const;
	void setUniform(GLint location, const glm::mat4& matrix) const;

	inline GLint attributeLocation(const std::string& name) const { return glGetAttribLocation(m_id.value, name.c_str()); }

private:

	void retrieveUniforms();

	struct ID {
		ID() : value{ glCreateProgram() } {}
		~ID() { release(); }
		void release() { glDeleteProgram(value); value = 0; }
		GLuint value{ 0 };
	} m_id;

	std::unordered_map<std::string, UniformInfo> m_uniforms{};

};