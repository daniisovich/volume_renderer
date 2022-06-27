#pragma once

#include <glad/glad.h>

#include <vector>


class glVbo {

public:

	glVbo() = delete;
	glVbo(const glVbo&) = delete;
	glVbo& operator=(const glVbo&) = delete;

	glVbo(const std::vector<float>& data);
	glVbo(const std::vector<uint32_t>& data);
	glVbo(glVbo&& other) noexcept;
	~glVbo();

private:

	GLuint m_id;

};