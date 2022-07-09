#pragma once

#include <glm/glm.hpp>


namespace dvr {
	
	class Camera {

	public:

		Camera(const glm::vec3& position, const glm::vec3& look_at, const glm::vec3& up, float fov_deg, int width, int height);
		Camera() = delete;

		void setProjection(uint32_t width, uint32_t height);

		glm::mat4 vp() const;

	private:

		glm::mat4 m_view;
		glm::mat4 m_proj;

		const float m_fov_deg;

	};

}
