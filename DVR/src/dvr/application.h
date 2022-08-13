#pragma once

#include "dvr/window/glfw_window.h"
#include "dvr/window/controller.h"
#include "dvr/renderer/volume_renderer.h"


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
