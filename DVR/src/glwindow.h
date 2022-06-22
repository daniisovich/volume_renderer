#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>


class GLWindow {

public:

	GLWindow();
	GLWindow(int width, int height, const std::string& name);
	~GLWindow();

	inline bool shouldClose() const { return glfwWindowShouldClose(m_window); }
	inline void swapAndPoll() const {
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

private:

	GLFWwindow* m_window;

};