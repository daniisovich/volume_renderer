#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>


struct DestroyGLFWwindow {
	void operator()(GLFWwindow* window) {
		glfwDestroyWindow(window);
	}
};
using unique_GLFWwindow = std::unique_ptr<GLFWwindow, DestroyGLFWwindow>;


class GLWindow {

public:

	GLWindow();
	GLWindow(int width, int height, const std::string& name);
	~GLWindow();

	inline bool shouldClose() const { return glfwWindowShouldClose(m_window.get()); }
	inline void swapAndPoll() const {
		glfwSwapBuffers(m_window.get());
		glfwPollEvents();
	}

private:

	unique_GLFWwindow m_window;

};