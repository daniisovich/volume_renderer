#include "gl_vbo.h"


glVbo::glVbo(const std::vector<float>& data) : m_id{} {
	glNamedBufferData(m_id.value, sizeof(GLfloat) * data.size(), data.data(), GL_STATIC_DRAW);
}

glVbo::glVbo(const std::vector<uint32_t>& data) : m_id{} {
	glNamedBufferData(m_id.value, sizeof(GLuint) * data.size(), data.data(), GL_STATIC_DRAW);
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
