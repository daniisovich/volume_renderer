#pragma once

#include <glad/glad.h>

#include <string>


struct ShaderInfo {
	GLenum type;
	std::string_view path;
};

class glShader {

public:

	glShader(ShaderInfo info);

	glShader() = delete;
	glShader(const glShader&) = delete;
	glShader& operator=(const glShader&) = delete;
	~glShader() = default;

	glShader(glShader&& other) noexcept;
	glShader& operator=(glShader&& other) noexcept;

	inline GLuint id() const { return m_id.value; }

private:

	struct ID {
		ID(GLenum type) : value{ glCreateShader(type) } {}
		~ID() { release(); }
		void release() { glDeleteShader(value); value = 0; }
		GLuint value{ 0 };
	} m_id;
};