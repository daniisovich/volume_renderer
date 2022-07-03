#include "unit_cube.h"

#include <glm/gtc/matrix_transform.hpp>


UnitCube::UnitCube(int32_t position_location) : m_vao{} {
	m_vao.add(m_vertices, position_location, 3, 3 * sizeof(float));
	m_vao.add(m_indices);
}

glm::mat4 UnitCube::modelMatrix() {
	
	static Rotation previous_rotation{ 0.0f, 0.0f };
	if (previous_rotation.theta != m_rotation.theta || previous_rotation.phi != m_rotation.phi) {
		updateRotationMatrix();
		previous_rotation = m_rotation;
	}
	return m_model_matrix;

}

void UnitCube::addRotation(const Rotation& rotation) {

	m_rotation.theta += rotation.theta;
	m_rotation.phi += rotation.phi;

	uint32_t complete_rotations = uint32_t(m_rotation.theta / 360.0f);
	m_rotation.theta -= complete_rotations * 360.0f;

	complete_rotations = uint32_t(m_rotation.phi / 360.0f);
	m_rotation.phi -= complete_rotations * 360.0f;

}

void UnitCube::updateRotationMatrix() {
	m_model_matrix = glm::rotate(glm::mat4{ 1.0f }, glm::radians(m_rotation.phi), glm::vec3(1.0f, 0.0f, 0.0f));
	m_model_matrix = glm::rotate(m_model_matrix, glm::radians(m_rotation.theta), glm::vec3(0.0f, 1.0f, 0.0f));
}