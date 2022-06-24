#include "gl_vbo.h"


glVbo::glVbo(const std::vector<float>& data) {

	glGenBuffers(1, &m_id);

	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), GL_STATIC_DRAW);

}

glVbo::glVbo(const std::vector<int>& data) {

	glGenBuffers(1, &m_id);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * data.size(), data.data(), GL_STATIC_DRAW);

}

glVbo::glVbo(glVbo&& other) noexcept : m_id{ other.m_id } {
	other.m_id = 0;
}

glVbo::~glVbo() {
	glDeleteBuffers(1, &m_id);
}
