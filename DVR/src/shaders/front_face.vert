#version 460 core

layout (location = 0) in vec3 vert_position;
layout (location = 1) in vec3 vert_color;
out vec3 frag_color;

void main() {
	gl_Position = vec4(vert_position, 1.0);
	frag_color = vert_color;
}