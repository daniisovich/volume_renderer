#pragma once

#include <glad/glad.h>

#include <vector>


class glVao {

public:

	glVao(const glVao&) = delete;
	glVao& operator=(const glVao&) = delete;

	glVao();
	glVao(glVao&& other) noexcept;
	~glVao();

	void add(const std::vector<float>& data, int attrib_location, int attrib_size, int stride, int offset = 0, bool normalized = false) const;
	void add(const std::vector<uint32_t>& data) const;

	inline void bind() const { glBindVertexArray(m_id); }
	inline void unbind() const { glBindVertexArray(0); }

private:

	GLuint m_id;

};