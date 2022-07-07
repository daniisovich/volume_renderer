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


struct SmoothStepParameter {
	float start;
	float end;
};


class Controller {

public:

	Controller() = default;

	void setCallbacks(GLFWwindow* window) const;

	void setRotationSpeed(double frametime);

	inline SmoothStepParameter smoothStepParameter() const { return m_smooth_step_parameter; }
	inline void attachRenderer(const std::shared_ptr<VolumeRenderer> renderer) { m_renderer = renderer; }

private:

	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	void addSmoothStepStart(float delta);
	void addSmoothStepEnd(float delta);

	std::shared_ptr<VolumeRenderer> m_renderer;

	bool m_left_click{ false };

	double m_speed{ 0.1 };
	SmoothStepParameter m_smooth_step_parameter{ 0.1f, 0.3f };
	const float m_smooth_step_factor{ 0.01f };

};