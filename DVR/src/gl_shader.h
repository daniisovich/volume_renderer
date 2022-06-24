#pragma once

#include <glad/glad.h>

#include <string>


struct ShaderInfo {
	GLenum type;
	std::string_view path;
};


class glShader {

public:

	glShader() = default;
	glShader(const glShader&) = delete;
	glShader& operator=(const glShader&) = delete;
	
	glShader(glShader&& other) noexcept;
	~glShader();
	void load(ShaderInfo info);

	inline GLuint id() const { return m_id; }

private:

	GLuint m_id{ 0 };

};