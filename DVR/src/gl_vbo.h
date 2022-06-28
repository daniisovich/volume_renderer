#pragma once

#include <glad/glad.h>

#include <vector>


class glVbo {

public:

	glVbo(const std::vector<float>& data);
	glVbo(const std::vector<uint32_t>& data);

	glVbo() = delete;
	glVbo(const glVbo&) = delete;
	glVbo& operator=(const glVbo&) = delete;
	~glVbo() = default;

	glVbo(glVbo&& other) noexcept;
	glVbo& operator=(glVbo&& other) noexcept;

private:

	struct ID {
		ID() { glCreateBuffers(1, &value); }
		~ID() { release(); }
		void release() { glDeleteBuffers(1, &value); value = 0; }
		GLuint value{ 0 };
	} m_id;

};