#version 460 core

layout (location = 0) in vec3 vert_position;
out vec3 frag_position;

void main() {
	gl_Position = vec4(vert_position, 1.0);
	frag_position = vert_position + 0.5;
}