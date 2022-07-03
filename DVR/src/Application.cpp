#include "Application.h"

#include <chrono>


Application::Application(const std::array<uint32_t, 2>& viewport_size) : m_controller{}, m_window { m_controller }, m_volume_renderer{ std::make_shared<VolumeRenderer>(viewport_size) }
{
	m_controller.attachRenderer(m_volume_renderer);
}

void Application::run() {

	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	while (!m_window.shouldClose()) {

		m_volume_renderer->render();

		if (m_controller.showFramerate()) {

		}

		m_window.swapAndPoll();

	}

}

double Application::frametime() const {

	using time_point = std::chrono::high_resolution_clock::time_point;
	static time_point last_time{ std::chrono::high_resolution_clock::now() };
	time_point current_time{ std::chrono::high_resolution_clock::now() };

	auto delta = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - last_time);
	double frametime = delta.count();

	last_time = std::chrono::high_resolution_clock::now();
	return frametime;

}