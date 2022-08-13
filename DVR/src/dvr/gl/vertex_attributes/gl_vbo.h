#pragma once

#include <glad/glad.h>


namespace dvr::gl {

	class Vbo {

	public:

		Vbo(const std::vector<float>& data);
		Vbo(const std::vector<uint32_t>& data);

		Vbo() = delete;
		Vbo(const Vbo&) = delete;
		Vbo& operator=(const Vbo&) = delete;
		~Vbo() = default;

		Vbo(Vbo&& other) noexcept;
		Vbo& operator=(Vbo&& other) noexcept;

		GLuint id() const { return m_id.value; }

	private:

		struct ID {
			ID() { glCreateBuffers(1, &value); }
			~ID() { release(); }
			void release() { glDeleteBuffers(1, &value); value = 0; }
			GLuint value{ 0 };
		} m_id;

	};

}
