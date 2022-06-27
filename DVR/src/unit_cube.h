#pragma once

#include <vector>

#include "gl_vao.h"


class UnitCube {

public:

	UnitCube(int32_t position_location);

	inline void bind() const { m_vao.bind(); }
	inline void unbind() const { m_vao.unbind(); }

	inline void draw() const { glDrawElements(GL_TRIANGLES, GLsizei(m_indices.size()), GL_UNSIGNED_INT, 0); }

private:

	glVao m_vao;

	
	const std::vector<float> m_vertices{
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
	};

	const std::vector<uint32_t> m_indices{
		0, 2, 3, 0, 3, 1,
		2, 6, 7, 2, 7, 3,
		6, 4, 5, 6, 5, 7,
		4, 0, 1, 4, 1, 5,
		0, 4, 6, 0, 6, 2,
		1, 7, 5, 1, 3, 7,
	};

};