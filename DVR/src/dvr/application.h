#pragma once

#include "window/glfw_window.h"
#include "window/controller.h"
#include "renderer/volume_renderer.h"


namespace dvr {

	class Application {

	public:

		Application(const std::array<uint32_t, 2>& viewport_size);
		void run();

	private:

		double frametime() const;

		glfw::Controller m_controller;
		glfw::Window m_window;
		std::shared_ptr<renderer::VolumeRenderer> m_volume_renderer;

	};

}
