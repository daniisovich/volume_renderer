#include "gl_window.h"

#include <stdexcept>

#include "gl_debug.h"


glWindow::glWindow() : glWindow { 800, 600, "Window" } {}

glWindow::glWindow(uint32_t width, uint32_t height, const std::string_view name) {

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
	setCallbacks();

	glViewport(0, 0, width, height);
	
}

glWindow::~glWindow() {
	release();
	glfwTerminate();
}

glWindow::glWindow(glWindow&& other) noexcept : m_window{ other.m_window } {
	other.m_window = nullptr;
}

glWindow& glWindow::operator=(glWindow&& other) noexcept {

	if (this != &other) {
		release();
		std::swap(m_window, other.m_window);
	}
	return *this;
}

void glWindow::release() {
	glfwDestroyWindow(m_window);
	m_window = nullptr;
}

std::pair<uint32_t, uint32_t> glWindow::size() const {

	int width{ 0 }, height{ 0 };
	glfwGetWindowSize(m_window, &width, &height);
	return { width, height };

}