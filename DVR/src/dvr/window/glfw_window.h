#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "controller.h"


namespace dvr {
	namespace glfw {

		class Window {

		public:

			Window(const Controller& controller);
			Window(uint32_t width, uint32_t height, const std::string_view name, const Controller& controller);
			~Window();

			Window(const Window&) = delete;
			Window& operator=(const Window&) = delete;

			Window(Window&& other) noexcept;
			Window& operator=(Window&& other) noexcept;

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

	}
}