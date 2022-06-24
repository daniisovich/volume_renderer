#include <glm/glm.hpp>

#include <iostream>
#include <vector>

#include "gl_window.h"
#include "gl_program.h"
#include "unit_cube.h"


void renderVolume(const glWindow& window) {

	glProgram program;
	program.load({ {GL_VERTEX_SHADER, "src/shaders/front_face.vert"}, {GL_FRAGMENT_SHADER, "src/shaders/front_face.frag"} });
	
	GLuint vertex_position_loc{ program.attributeLocation("vert_position") };

	UnitCube cube{ vertex_position_loc };


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	program.enable();
	cube.bind();

	while (!window.shouldClose()) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, cube.indexCount(), GL_UNSIGNED_INT, 0);

		window.swapAndPoll();

	}

	cube.unbind();
	program.disable();

}


int main() {
	
	std::cout << "Direct Volume Renderer start" << std::endl;

	try {

		glWindow window{};
		renderVolume(window);

	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}	

	return EXIT_SUCCESS;

}