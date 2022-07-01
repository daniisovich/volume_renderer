#pragma once

#include <glm/glm.hpp>


struct Rotation {
	float theta;
	float phi;
};

class Camera {

public:

	Camera(const glm::vec3& position, const glm::vec3& look_at, const glm::vec3& up, float fov_deg, int width, int height);
	Camera() = delete;

	void resetRotation() { m_rotation = { 0.0f, 0.0f }; }
	void addRotation(const Rotation& rotation);

	glm::mat4 mvp();

private:

	void updateRotationMatrix();

	Rotation m_rotation{ 0.0f, 0.0f };
	glm::mat4 m_rotation_matrix;

	glm::mat4 m_view;
	glm::mat4 m_proj;

};