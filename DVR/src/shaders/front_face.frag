#version 460 core

in vec3 frag_position;
out vec4 color;


void main() {
	color = vec4(frag_position, 1.0);
}