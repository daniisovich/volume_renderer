#pragma once

#include <glm/glm.hpp>


class Camera {

public:

	Camera(const glm::vec3& position, const glm::vec3& look_at, const glm::vec3& up);

	void setRotationAngle(double angle) { m_angle = angle; }

private:

	double m_angle{ 0 };
	glm::mat4 m_rotation;
	glm::mat4 m_view;
	glm::mat4 m_proj;

};