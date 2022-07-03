#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

#include "volume_renderer.h"
#include "camera.h"
#include "unit_cube.h"
#include "gl_framebuffer.h"


class Controller {

public:

	Controller() = default;

	void setCallbacks(GLFWwindow* window) const;

	void setRotationSpeed(double frametime);

	inline bool showFramerate() const { return m_show_framerate; }
	inline void attachRenderer(const std::shared_ptr<VolumeRenderer> renderer) { m_renderer = renderer; }

private:

	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	std::shared_ptr<VolumeRenderer> m_renderer;

	bool m_left_click{ false }, m_right_click{ false };
	bool m_show_framerate{ false };

	float m_rotation_speed{ 0.1f };

};