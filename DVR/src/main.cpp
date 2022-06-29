#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <vector>

#include "gl_window.h"
#include "gl_program.h"
#include "gl_framebuffer.h"
#include "gl_texture.h"

#include "camera.h"
#include "window_callbacks.h"
#include "unit_cube.h"


void renderVolume() {

	auto controller{ Controller::instance() };
	glWindow window{ controller };

	glProgram first_pass(std::vector<ShaderInfo>{{GL_VERTEX_SHADER, "src/shaders/front_face.vert"}, {GL_FRAGMENT_SHADER, "src/shaders/front_face.frag"}});
	glProgram second_pass(std::vector<ShaderInfo>{{GL_VERTEX_SHADER, "src/shaders/front_face.vert"}, {GL_FRAGMENT_SHADER, "src/shaders/back_face.frag"}});

	GLint vertex_position_loc{ 0 };
	UnitCube cube{ vertex_position_loc };

	auto [width, height] = window.size();
	glTexture2D front_face_tex{ GL_RGBA8, width, height };
	glFramebuffer front_faces{front_face_tex, 0, 0};

	Camera camera({ 0.0f, 0.0f, 3.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });

	glm::mat4 model{ glm::mat4(1.0f) };
	model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 view{ glm::lookAt(glm::vec3{0.0f, 0.0f, 3.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}) };
	glm::mat4 proj{ glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f) };

	glm::mat4 mvp = proj * view * model;
	
	struct {
		GLint front_faces{ 0 };
	}uniform_bindings;

	first_pass.setUniform("mvp", mvp);

	second_pass.setUniform("mvp", mvp);
	front_face_tex.activate(uniform_bindings.front_faces);

	cube.bind();

	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	while (!window.shouldClose()) {

		front_faces.bind();
		glClear(GL_COLOR_BUFFER_BIT);
		glCullFace(GL_FRONT);

		first_pass.enable();
		cube.draw();

		front_faces.unbind();
		glClear(GL_COLOR_BUFFER_BIT);
		glCullFace(GL_BACK);

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