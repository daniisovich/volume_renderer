#include "unit_cube.h"


UnitCube::UnitCube(unsigned int position_location) : m_vao{} {
	m_vao.add(m_vertices, position_location, 3, 3 * sizeof(float));
	m_vao.add(m_indices);
}