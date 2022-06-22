#include "glwindow.h"

#include <stdexcept>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


GLWindow::GLWindow() : GLWindow{ 800, 600, "Window" } {}

GLWindow::GLWindow(int width, int height, const std::string& name) {

	if (!glfwInit())
		throw std::runtime_error("Failed to initialize GLFW");
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	if (!m_window) {
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		throw std::runtime_error("Failed to initialize GLAD");
	}

	glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	glfwSetKeyCallback(m_window, key_callback);

}

GLWindow::~GLWindow() {

	glfwDestroyWindow(m_window);
	glfwTerminate();

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

}