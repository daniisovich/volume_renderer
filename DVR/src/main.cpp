#include <glm/glm.hpp>

#include <iostream>
#include <vector>

#include "gl_window.h"
#include "gl_program.h"


void renderVolume(const glWindow& window) {
	/*
	struct {
		const std::vector<glm::vec3> vertices{
			{-1.0f,  1.0f,  1.0f},
			{-1.0f, -1.0f,  1.0f},
			{ 1.0f,  1.0f,  1.0f},
			{ 1.0f, -1.0f,  1.0f},

			{-1.0f,  1.0f, -1.0f},
			{-1.0f, -1.0f, -1.0f},
			{ 1.0f,  1.0f, -1.0f},
			{ 1.0f, -1.0f, -1.0f},
		};

		const std::vector<GLint> indices{
			0, 2, 3, 0, 3, 1,
			2, 6, 7, 2, 7, 3,
			6, 4, 5, 6, 5, 7,
			4, 0, 1, 4, 1, 5,
			0, 4, 6, 0, 6, 2,
			1, 5, 7, 1, 7, 3,
		};
	} cube;
	*/

	struct {
		const std::vector<glm::vec3> vertices{
			{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f},
			{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f},
			{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f},
			{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.0f},
		};
		const std::vector<GLint> indices{
			0, 1, 3,
			1, 2, 3,
		};
	} cube;

	glProgram program;
	program.load({ {GL_VERTEX_SHADER, "src/shaders/front_face.vert"}, {GL_FRAGMENT_SHADER, "src/shaders/front_face.frag"} });
	
	GLuint cube_vao{ 0 };
	glGenVertexArrays(1, &cube_vao);
	glBindVertexArray(cube_vao);
	
	struct {
		GLuint vertex{ 0 };
		GLuint index{ 0 };
	} cube_buffer;
	int num_buffer{ sizeof(cube_buffer) / sizeof(GLuint)};
	glGenBuffers(num_buffer, &cube_buffer.vertex);
	
	glBindBuffer(GL_ARRAY_BUFFER, cube_buffer.vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * cube.vertices.size(), cube.vertices.data(), GL_STATIC_DRAW);

	GLuint vertex_position_loc{ program.attributeLocation("vert_position") };
	glVertexAttribPointer(vertex_position_loc, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(vertex_position_loc);

	GLuint vertex_color_loc{ program.attributeLocation("vert_color") };
	glVertexAttribPointer(vertex_color_loc, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(vertex_color_loc);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_buffer.index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * cube.indices.size(), cube.indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glDeleteBuffers(num_buffer, &cube_buffer.vertex);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	program.enable();
	glBindVertexArray(cube_vao);

	while (!window.shouldClose()) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, cube.indices.size(), GL_UNSIGNED_INT, 0);

		window.swapAndPoll();

	}

	glBindVertexArray(0);
	program.disable();

	glDeleteVertexArrays(1, &cube_vao);

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