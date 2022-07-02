#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <vector>

#include "gl_window.h"
#include "gl_program.h"
#include "gl_framebuffer.h"
#include "gl_texture2d.h"

#include "camera.h"
#include "window_callbacks.h"
#include "unit_cube.h"
#include "utility.h"


void renderVolume() {

	auto controller{ Controller::instance() };
	glWindow window{ controller };

	glProgram first_pass(std::vector<ShaderInfo>{{GL_VERTEX_SHADER, "src/shaders/front_face.vert"}, {GL_FRAGMENT_SHADER, "src/shaders/front_face.frag"}});
	glProgram second_pass(std::vector<ShaderInfo>{{GL_VERTEX_SHADER, "src/shaders/front_face.vert"}, {GL_FRAGMENT_SHADER, "src/shaders/back_face.frag"}});

	GLint vertex_position_loc{ 0 };
	UnitCube cube{ vertex_position_loc };

	auto [width, height] = window.size();
	glTexture2D front_face_tex{ GL_RGBA8, {width, height} };
	glFramebuffer front_faces{front_face_tex, 0, 0};

	auto camera = std::make_shared<Camera>(Camera({ 0.0f, 0.0f, 3.0f }, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, 45.0f, 800, 600));
	controller->attachCamera(camera);

	const GLint num_samples{ 128 };
	const GLfloat smooth_step_start{ 0.12f };
	const GLfloat smooth_step_end{ 0.22f };

	second_pass.setUniform("num_samples", num_samples);
	second_pass.setUniform("smooth_step_start", smooth_step_start);
	second_pass.setUniform("smooth_step_end", smooth_step_end);

	struct {
		GLuint front_faces{ 0 };
		GLuint volume{ 1 };
	} uniform_bindings;

	front_face_tex.activate(uniform_bindings.front_faces);

	const std::string_view volume_path{ "data/bonsai.dat" };
	glTexture3D volume_tex{ utility::loadVolume(volume_path) };
	volume_tex.activate(uniform_bindings.volume);

	cube.bind();

	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	while (!window.shouldClose()) {

		glm::mat4 mvp = camera->mvp();

		front_faces.bind();
		glClear(GL_COLOR_BUFFER_BIT);
		glCullFace(GL_FRONT);

		first_pass.setUniform("mvp", mvp);
		first_pass.enable();
		cube.draw();

		front_faces.unbind();
		glClear(GL_COLOR_BUFFER_BIT);
		glCullFace(GL_BACK);

		second_pass.setUniform("mvp", mvp);
		second_pass.enable();
		cube.draw();

		window.swapAndPoll();

	}

}


int main() {

	try {
		renderVolume();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}	

	return EXIT_SUCCESS;

}