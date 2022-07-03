#include "controller.h"

#include <array>

#include <glm/glm.hpp>


void Controller::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	
	if (m_renderer) {
		m_renderer->setCameraProjection(width, height);
		glFramebuffer resized_framebuffer{ GL_RGBA8, {uint32_t(width), uint32_t(height)}, 0, 0 };
		m_renderer->setFramebuffer(resized_framebuffer);
	}
	else {
		printf("Callback::Warning::No renderer attached");
	}

	glViewport(0, 0, width, height);

}

void Controller::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	} 
	else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		if (m_renderer) {
			m_renderer->resetRotation();
		}
		else {
			printf("Callback::Warning::No renderer attached");
		}
	}
	else if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		m_show_framerate = !m_show_framerate;
	}

}

void Controller::CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	
	static std::array<double, 2> previous_pos{ xpos, ypos };
	
	if (m_left_click) {

		const std::array<double, 2> delta{ xpos - previous_pos[0], ypos - previous_pos[1] };
		const Rotation rotation{ m_rotation_speed * float(delta[0]), m_rotation_speed * float(delta[1]) };
		
		if (m_renderer) {
			m_renderer->addRotation(rotation);
		}
		else {
			printf("Callback::Warning::No renderer attached");
		}

	}

	previous_pos = { xpos, ypos };
	
}

void Controller::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		m_left_click = (action == GLFW_PRESS);
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		m_right_click = (action == GLFW_PRESS);
	}

}

void Controller::setCallbacks(GLFWwindow* window) const {

	glfwSetWindowUserPointer(window, (void*)this);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { static_cast<Controller*>(glfwGetWindowUserPointer(window))->FramebufferSizeCallback(window, width, height); });
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) { static_cast<Controller*>(glfwGetWindowUserPointer(window))->KeyCallback(window, key, scancode, action, mods); });
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) { static_cast<Controller*>(glfwGetWindowUserPointer(window))->CursorPosCallback(window, xpos, ypos); });
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) { static_cast<Controller*>(glfwGetWindowUserPointer(window))->MouseButtonCallback(window, button, action, mods); });

}
