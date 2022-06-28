#pragma once

#include <glad/glad.h>

#include <vector>


class glVao {

public:

	glVao();
	~glVao();

	glVao(const glVao&) = delete;
	glVao& operator=(const glVao&) = delete;

	glVao(glVao&& other) noexcept;
	glVao& operator=(glVao&& other) noexcept;

	void add(const std::vector<float>& data, int attrib_location, int attrib_size, int stride, int offset = 0, bool normalized = false) const;
	void add(const std::vector<uint32_t>& data) const;

	inline void bind() const { glBindVertexArray(m_id); }
	inline void unbind() const { glBindVertexArray(0); }

private:

	void release();

	GLuint m_id{ 0 };

};