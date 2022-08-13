#include "application.h"

#include <chrono>


namespace dvr {

	Application::Application(const std::array<uint32_t, 2>& viewport_size) : m_controller{}, m_window{ m_controller }, m_volume_renderer{ std::make_shared<renderer::VolumeRenderer>(viewport_size) }
	{
		m_controller.attachRenderer(m_volume_renderer);
	}

	void Application::run() {

		glEnable(GL_CULL_FACE);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		double frametime{ 0.0 };
		while (!m_window.shouldClose()) {

			frametime = this->frametime();
			m_controller.setRotationSpeed(frametime);
			auto [smooth_step_start, smooth_step_end] = m_controller.smoothStepParameter();
			m_volume_renderer->render(smooth_step_start, smooth_step_end);

			m_window.swapAndPoll();

		}

	}

	double Application::frametime() const {

		using clock = std::chrono::high_resolution_clock;
		static clock::time_point last_time{ clock::now() };
		clock::time_point current_time{ clock::now() };

		auto delta = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - last_time);
		double frametime = delta.count();

		last_time = current_time;
		return frametime;

	}

}