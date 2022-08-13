#pragma once

#include "dvr/gl/shader_program/gl_program.h"
#include "dvr/gl/texture/gl_texture2d.h"
#include "dvr/gl/texture/gl_texture3d.h"
#include "dvr/gl/gl_framebuffer.h"
#include "dvr/model/unit_cube.h"
#include "dvr/camera/camera.h"


namespace dvr {
	namespace renderer {

		class VolumeRenderer {

		public:

			VolumeRenderer() = delete;
			VolumeRenderer(const std::array<uint32_t, 2>& viewport_size);

			void render(float smooth_step_start, float smooth_step_end);

			void setCameraProjection(uint32_t width, uint32_t height) { m_camera.setProjection(width, height); }
			void setFramebuffer(gl::Framebuffer& framebuffer) { m_front_faces = std::move(framebuffer); }
			void resetRotation() { m_cube.resetRotation(); }
			void addRotation(const Rotation& rotation) { m_cube.addRotation(rotation); }

		private:

			gl::Program m_first_pass, m_second_pass;

			gl::Framebuffer m_front_faces;
			gl::Texture3D m_volume_tex;

			UnitCube m_cube;
			Camera m_camera;

			const GLfloat num_samples{ 32 };

			const struct {
				GLuint front_faces{ 0 };
				GLuint volume{ 1 };
			} uniform_bindings;

		};

	}
}
