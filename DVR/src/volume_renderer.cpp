#include "volume_renderer.h"

#include "utility.h"

VolumeRenderer::VolumeRenderer(const std::array<uint32_t, 2>& viewport_size) : 
	m_first_pass(std::vector<ShaderInfo>{ {GL_VERTEX_SHADER, "src/shaders/pass.vert"}, { GL_FRAGMENT_SHADER, "src/shaders/front_face.frag" }}),
	m_second_pass(std::vector<ShaderInfo>{ {GL_VERTEX_SHADER, "src/shaders/pass.vert"}, { GL_FRAGMENT_SHADER, "src/shaders/back_face.frag" }}),
	m_front_faces{ GL_RGBA8, viewport_size, 0, 0 },
	m_volume_tex{ utility::loadVolume("data/bonsai.dat") }, 
	m_cube{ m_first_pass.attributeLocation("vert_position") },
	m_camera{ { 0.0f, 0.0f, 3.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, viewport_size[0], viewport_size[1] }
{

	m_second_pass.setUniform("num_samples", num_samples);
	m_second_pass.setUniform("smooth_step_start", smooth_step_start);
	m_second_pass.setUniform("smooth_step_end", smooth_step_end);

	m_volume_tex.activate(uniform_bindings.volume);

	m_cube.bind();

}

void VolumeRenderer::render() {

	glm::mat4 mvp = m_camera.vp() * m_cube.modelMatrix();

	m_front_faces.bind();
	glClear(GL_COLOR_BUFFER_BIT);
	glCullFace(GL_FRONT);

	m_first_pass.setUniform("mvp", mvp);
	m_first_pass.enable();
	glDrawElements(GL_TRIANGLES, m_cube.indexCount(), GL_UNSIGNED_INT, 0);

	m_front_faces.unbind();
	glClear(GL_COLOR_BUFFER_BIT);
	glCullFace(GL_BACK);

	m_second_pass.setUniform("mvp", mvp);
	m_front_faces.activateTexture(uniform_bindings.front_faces);
	m_second_pass.enable();
	glDrawElements(GL_TRIANGLES, m_cube.indexCount(), GL_UNSIGNED_INT, 0);

}