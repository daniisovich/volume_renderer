#pragma once

#include <memory>

#include "gl_window.h"
#include "volume_renderer.h"
#include "controller.h"


class Application {

public:

	Application(const std::array<uint32_t, 2>& viewport_size);
	void run();

private:

	double frametime() const;

	Controller m_controller;
	glWindow m_window;
	std::shared_ptr<VolumeRenderer> m_volume_renderer;

};