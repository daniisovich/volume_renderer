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

	glVertexArrayVertexBuffer(m_id, 0, vbo.id(), 0, stride);
	glEnableVertexArrayAttrib(m_id, attrib_location);
	glVertexArrayAttribFormat(m_id, attrib_location, attrib_size, GL_FLOAT, normalized, offset);
	glVertexArrayAttribBinding(m_id, attrib_location, 0);

}

void glVao::add(const std::vector<uint32_t>& data) const {
	glVbo ebo{ data };
	glVertexArrayElementBuffer(m_id, ebo.id());
}