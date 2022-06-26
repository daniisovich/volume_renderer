#pragma once

#include <vector>

#include "gl_vao.h"


class UnitCube {

public:

	UnitCube(unsigned int position_location);

	inline void bind() const { m_vao.bind(); }
	inline void unbind() const { m_vao.unbind(); }

	inline uint32_t indexCount() const { return uint32_t(m_indices.size()); }

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

	const std::vector<int> m_indices{
		0, 2, 3, 0, 3, 1,
		2, 6, 7, 2, 7, 3,
		6, 4, 5, 6, 5, 7,
		4, 0, 1, 4, 1, 5,
		0, 4, 6, 0, 6, 2,
		1, 7, 5, 1, 3, 7,
	};

};