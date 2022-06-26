#include "gl_window.h"

#include <stdexcept>

#include "gl_debug.h"
#include "window_callbacks.h"


glWindow::glWindow() : glWindow { 800, 600, "Window" } {}

glWindow::glWindow(int width, int height, const std::string_view name) {

	if (!glfwInit())
		throw std::runtime_error("Failed to initialize GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(width, height, name.data(), nullptr, nullptr);
	if (!m_window) {
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwDestroyWindow(m_window);
		glfwTerminate();
		throw std::runtime_error("Failed to initialize GLAD");
	}

	gl_debug::debug_callback();

	// the glfwWindowHint commands for context version produce error 1282
	glGetError();

	glViewport(0, 0, width, height);
	setCallbacks();
	
}

glWindow::glWindow(glWindow&& other) noexcept : m_window{ other.m_window } {
	other.m_window = nullptr;
}

glWindow::~glWindow() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

std::pair<int, int> glWindow::size() const {
	int width{ 0 }, height{ 0 };
	glfwGetWindowSize(m_window, &width, &height);
	return { width, height };
}