#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(const glm::vec3& position, const glm::vec3& look_at, const glm::vec3& up, float fov_deg, int width, int height) : 
	m_proj{ glm::perspective(glm::radians(fov_deg), width / float(height), 0.1f, 100.0f)},
	m_view{ glm::lookAt(position, look_at, up) },
	m_rotation_matrix{ glm::mat4(1.0f) } {
}

void Camera::addRotation(const Rotation& rotation) {
	
	m_rotation.theta += rotation.theta;
	m_rotation.phi += rotation.phi;

	uint32_t complete_rotations = m_rotation.theta / 360;
	m_rotation.theta -= complete_rotations * 360;

	complete_rotations = m_rotation.phi / 360;
	m_rotation.phi -= complete_rotations * 360;


}
void Camera::updateRotationMatrix() {
	m_rotation_matrix = glm::rotate(glm::mat4{ 1.0f }, glm::radians(m_rotation.phi), glm::vec3(1.0f, 0.0f, 0.0f));
	m_rotation_matrix = glm::rotate(m_rotation_matrix, glm::radians(m_rotation.theta), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::mvp() {

	static Rotation previous_rotation{ 0.0, 0.0 };
	
	if (previous_rotation.phi != m_rotation.phi || previous_rotation.theta != m_rotation.theta) {
		updateRotationMatrix();
		previous_rotation = m_rotation;
	}

	return m_proj * m_view * m_rotation_matrix;

}