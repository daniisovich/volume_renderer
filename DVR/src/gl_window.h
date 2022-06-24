#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>


class glWindow {

public:

	glWindow(const glWindow&) = delete;
	glWindow& operator=(const glWindow&) = delete;

	glWindow();
	glWindow(int width, int height, const std::string_view name);
	~glWindow();

	inline bool shouldClose() const { return glfwWindowShouldClose(m_window); }
	inline void swapAndPoll() const {
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

private:

	void setCallbacks() const;

	GLFWwindow* m_window;

};