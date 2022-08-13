#include "precompiled/pch.h"
#pragma hdrstop

#include "glfw_window.h"
#include "../gl/core/debug/gl_debug.h"


namespace dvr {
	namespace glfw {

		Window::Window(const Controller& controller) : Window{ 800, 600, "Window", controller } {}

		Window::Window(uint32_t width, uint32_t height, const std::string_view name, const Controller& controller) {

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

			gl::debug::callback();
			controller.setCallbacks(m_window);

			glViewport(0, 0, width, height);

		}

		Window::~Window() {
			release();
			glfwTerminate();
		}

		Window::Window(Window&& other) noexcept : m_window{ other.m_window } {
			other.m_window = nullptr;
		}

		Window& Window::operator=(Window&& other) noexcept {

			if (this != &other) {
				release();
				std::swap(m_window, other.m_window);
			}
			return *this;
		}

		void Window::release() {
			glfwDestroyWindow(m_window);
			m_window = nullptr;
		}

		std::pair<uint32_t, uint32_t> Window::size() const {

			int width{ 0 }, height{ 0 };
			glfwGetWindowSize(m_window, &width, &height);
			return { width, height };

		}

	}
}