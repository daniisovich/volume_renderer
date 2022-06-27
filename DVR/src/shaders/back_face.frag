#version 460 core

in vec3 frag_position;
out vec4 color;

layout (location = 1) uniform sampler2D front_faces;
layout (location = 2) uniform sampler3D volume;
layout (location = 3) uniform sampler1D transfer_function;


void main() {
	vec3 front_face = texelFetch(front_faces, ivec2(gl_FragCoord), 0).xyz;
	vec3 direction = frag_position - front_face;
	color = vec4(-direction, 1.0);
}