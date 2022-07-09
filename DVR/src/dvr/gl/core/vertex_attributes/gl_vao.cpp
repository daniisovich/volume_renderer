#include "gl_vao.h"

#include <vector>

#include "gl_vbo.h"


namespace dvr {
	namespace gl {

		Vao::Vao() {
			glCreateVertexArrays(1, &m_id);
		}

		Vao::~Vao() {
			release();
		}

		void Vao::release() {
			glDeleteVertexArrays(1, &m_id);
			m_id = 0;
		}

		Vao::Vao(Vao&& other) noexcept : m_id{ other.m_id } {
			other.m_id = 0;
		}

		Vao& Vao::operator=(Vao&& other) noexcept {

			if (this != &other) {
				release();
				std::swap(m_id, other.m_id);
			}
			return *this;

		}

		void Vao::add(const std::vector<float>& data, int attrib_location, int attrib_size, int stride, int offset, bool normalized) const {

			Vbo vbo{ data };

			glVertexArrayVertexBuffer(m_id, 0, vbo.id(), 0, stride);
			glEnableVertexArrayAttrib(m_id, attrib_location);
			glVertexArrayAttribFormat(m_id, attrib_location, attrib_size, GL_FLOAT, normalized, offset);
			glVertexArrayAttribBinding(m_id, attrib_location, 0);

		}

		void Vao::add(const std::vector<uint32_t>& data) const {
			Vbo ebo{ data };
			glVertexArrayElementBuffer(m_id, ebo.id());
		}

	}
}
