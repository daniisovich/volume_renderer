#include "controller.h"

#include <array>

#include <glm/glm.hpp>
#include <iostream>

void Controller::setRotationSpeed(double frametime) {
	m_speed = 50.0 * frametime;
}

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
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		if (m_renderer) {
			m_renderer->resetRotation();
		}
		else {
			printf("Callback::Warning::No renderer attached");
		}
	}
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		addSmoothStepEnd(m_speed * m_smooth_step_factor);
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		addSmoothStepEnd(-m_speed * m_smooth_step_factor);
	}
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		addSmoothStepStart(m_speed * m_smooth_step_factor);
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		addSmoothStepStart(-m_speed * m_smooth_step_factor);
	}

}

void Controller::addSmoothStepStart(float delta) {

	m_smooth_step_parameter.start += delta;
	m_smooth_step_parameter.start = (m_smooth_step_parameter.start >= 0.0f) ? m_smooth_step_parameter.start : 0.0f;
	m_smooth_step_parameter.start = (m_smooth_step_parameter.start <= m_smooth_step_parameter.end) ? m_smooth_step_parameter.start : m_smooth_step_parameter.end;

}

void Controller::addSmoothStepEnd(float delta) {

	m_smooth_step_parameter.end += delta;
	m_smooth_step_parameter.end = (m_smooth_step_parameter.end <= 1.0f) ? m_smooth_step_parameter.end : 1.0f;
	m_smooth_step_parameter.end = (m_smooth_step_parameter.start <= m_smooth_step_parameter.end) ? m_smooth_step_parameter.end : m_smooth_step_parameter.start;

}

void Controller::CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	
	static std::array<double, 2> previous_pos{ xpos, ypos };
	
	if (m_left_click) {

		const std::array<double, 2> delta{ xpos - previous_pos[0], ypos - previous_pos[1] };
		const Rotation rotation{ float(m_speed * delta[0]), float(m_speed * delta[1]) };
		
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

}

void Controller::setCallbacks(GLFWwindow* window) const {

	glfwSetWindowUserPointer(window, (void*)this);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { static_cast<Controller*>(glfwGetWindowUserPointer(window))->FramebufferSizeCallback(window, width, height); });
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) { static_cast<Controller*>(glfwGetWindowUserPointer(window))->KeyCallback(window, key, scancode, action, mods); });
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) { static_cast<Controller*>(glfwGetWindowUserPointer(window))->CursorPosCallback(window, xpos, ypos); });
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) { static_cast<Controller*>(glfwGetWindowUserPointer(window))->MouseButtonCallback(window, button, action, mods); });

}
