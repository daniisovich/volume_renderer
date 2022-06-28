#include "gl_vbo.h"


glVbo::glVbo(const std::vector<float>& data) : m_id{} {

	glBindBuffer(GL_ARRAY_BUFFER, m_id.value);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), GL_STATIC_DRAW);

}

glVbo::glVbo(const std::vector<uint32_t>& data) : m_id{} {

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id.value);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * data.size(), data.data(), GL_STATIC_DRAW);

}

glVbo::glVbo(glVbo&& other) noexcept : m_id{ other.m_id } {
	other.m_id.value = 0;
}

glVbo& glVbo::operator=(glVbo&& other) noexcept {

	if (this != &other) {
		m_id.release();
		std::swap(m_id, other.m_id);
	}
	return *this;

}
