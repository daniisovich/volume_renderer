#include "unit_cube.h"


UnitCube::UnitCube(int32_t position_location) : m_vao{} {
	m_vao.add(m_vertices, position_location, 3, 3 * sizeof(float));
	m_vao.add(m_indices);
}