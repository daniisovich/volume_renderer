#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>


namespace dvr {

	Camera::Camera(const glm::vec3& position, const glm::vec3& look_at, const glm::vec3& up, float fov_deg, int width, int height) :
		m_proj{ glm::perspective(glm::radians(fov_deg), width / float(height), 0.1f, 100.0f) },
		m_view{ glm::lookAt(position, look_at, up) }, m_fov_deg{ fov_deg } {
	}

	void Camera::setProjection(uint32_t width, uint32_t height) {
		glm::perspective(glm::radians(m_fov_deg), width / float(height), 0.1f, 100.0f);
	}

	glm::mat4 Camera::vp() const {
		return m_proj * m_view;
	}

}