#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

#include "camera.h"


class Controller {

public:

	static std::shared_ptr<Controller> create();
	static std::shared_ptr<Controller> instance();

	void setCallbacks(GLFWwindow* window) const;
	void attachCamera(const std::shared_ptr<Camera>& camera);

private:

	Controller() {};

	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);


	static std::shared_ptr<Controller> m_instance;
	std::shared_ptr<Camera> m_camera;

	bool m_rotate{ false };
	const float m_rotation_speed{ 0.1f };

};