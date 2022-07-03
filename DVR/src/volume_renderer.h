#pragma once

#include <memory>

#include "gl_program.h"
#include "gl_texture2d.h"
#include "gl_texture3d.h"
#include "gl_framebuffer.h"
#include "unit_cube.h"
#include "camera.h"


class VolumeRenderer {

public:

	VolumeRenderer() = delete;
	VolumeRenderer(const std::array<uint32_t, 2>& viewport_size);

	void render();

	void setCameraProjection(uint32_t width, uint32_t height) { m_camera.setProjection(width, height); }
	void setFramebuffer(glFramebuffer& framebuffer) { m_front_faces = std::move(framebuffer); }
	void resetRotation() { m_cube.resetRotation(); }
	void addRotation(const Rotation& rotation) { m_cube.addRotation(rotation); }

private:

	glProgram m_first_pass, m_second_pass;

	glFramebuffer m_front_faces;
	glTexture3D m_volume_tex;

	UnitCube m_cube;
	Camera m_camera;

	const GLfloat num_samples{ 32 };
	const GLfloat smooth_step_start{ 0.12f };
	const GLfloat smooth_step_end{ 0.22f };

	const struct {
		GLuint front_faces{ 0 };
		GLuint volume{ 1 };
	} uniform_bindings;

};