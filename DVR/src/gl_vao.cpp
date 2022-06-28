#include "gl_vao.h"

#include <vector>

#include "gl_vbo.h"


glVao::glVao() {
	glCreateVertexArrays(1, &m_id);
}

glVao::~glVao() {
	release();
}

void glVao::release() {
	glDeleteVertexArrays(1, &m_id);
	m_id = 0;
}

glVao::glVao(glVao&& other) noexcept : m_id{ other.m_id } {
	other.m_id = 0;
}

glVao& glVao::operator=(glVao&& other) noexcept {

	if (this != &other) {
		release();
		std::swap(m_id, other.m_id);
	}
	return *this;

}

void glVao::add(const std::vector<float>& data, int attrib_location, int attrib_size, int stride, int offset, bool normalized) const {

	glVbo vbo{ data };

	bind();
	glVertexAttribPointer(attrib_location, attrib_size, GL_FLOAT, normalized, stride, (void*)offset);
	glEnableVertexAttribArray(attrib_location);
	unbind();

}

void glVao::add(const std::vector<uint32_t>& data) const {

	bind();
	glVbo ebo{ data };
	unbind();

}