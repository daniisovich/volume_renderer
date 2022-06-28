#version 460 core

in vec3 frag_position;
out vec4 color;

layout (binding = 0) uniform sampler2D front_faces;
layout (binding = 1) uniform sampler3D volume;
layout (binding = 2) uniform sampler1D transfer_function;


void main() {
	vec3 front_face = texelFetch(front_faces, ivec2(gl_FragCoord), 0).xyz;
	vec3 direction = frag_position - front_face;
	color = vec4(-direction, 1.0);
}