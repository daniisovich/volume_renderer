#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "controller.h"


class glWindow {

public:

	glWindow(const Controller& controller);
	glWindow(uint32_t width, uint32_t height, const std::string_view name, const Controller& controller);
	~glWindow();

	glWindow(const glWindow&) = delete;
	glWindow& operator=(const glWindow&) = delete;

	glWindow(glWindow&& other) noexcept;
	glWindow& operator=(glWindow&& other) noexcept;	

	std::pair<uint32_t, uint32_t> size() const;

	inline bool shouldClose() const { return glfwWindowShouldClose(m_window); }
	inline void swapAndPoll() const {
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	inline const GLFWwindow* window() const { return m_window; }

private:

	void release();

	GLFWwindow* m_window;

};