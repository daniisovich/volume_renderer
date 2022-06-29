#pragma once

#include <GLFW/glfw3.h>

#include <memory>

#include "camera.h"


class Controller {

public:

	static std::shared_ptr<Controller> create();
	static std::shared_ptr<Controller> instance();

	void setCallbacks(GLFWwindow* window) const;

	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

private:

	Controller() {};

	bool m_rotate{ false };
	double m_rotation_angle{ 0 };

	static std::shared_ptr<Controller> m_instance;

};