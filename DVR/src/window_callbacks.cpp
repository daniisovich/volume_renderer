#include "window_callbacks.h"

#include <glm/glm.hpp>

std::shared_ptr<Controller> Controller::m_instance;


void Controller::setCallbacks(GLFWwindow* window) const {

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { m_instance->FramebufferSizeCallback(window, width, height); });
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) { m_instance->KeyCallback(window, key, scancode, action, mods); });
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) { m_instance->CursorPosCallback(window, xpos, ypos); });
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) { m_instance->MouseButtonCallback(window, button, action, mods); });

}

void Controller::attachCamera(const std::shared_ptr<Camera>& camera) {
	m_camera = camera;
}

std::shared_ptr<Controller> Controller::create() {
	struct MakeSharedController : public Controller {};
	return std::make_shared<MakeSharedController>();
}

std::shared_ptr<Controller> Controller::instance() {
	if (!m_instance)
		m_instance = create();
	return m_instance;
}


void Controller::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Controller::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	} else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		m_camera->resetRotation();
	}

}

void Controller::CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	
	static double previous_xpos{ xpos }, previous_ypos{ ypos };
	
	if (m_rotate) {

		double delta_x = xpos - previous_xpos;
		double delta_y = ypos - previous_ypos;

		float theta = m_rotation_speed * float(delta_x);
		float phi = m_rotation_speed * float(delta_y);

		m_camera->addRotation({ theta, phi });

	}

	previous_xpos = xpos;
	previous_ypos = ypos;
	
}

void Controller::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			m_rotate = true;
		} else if (action == GLFW_RELEASE) {
			m_rotate = false;
		}
	}
}
