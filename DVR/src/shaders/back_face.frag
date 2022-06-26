#version 460 core

in vec3 frag_position;
out vec4 color;

uniform sampler2D front_faces;


void main() {
	vec3 front_face = texelFetch(front_faces, ivec2(gl_FragCoord), 0).xyz;
	vec3 direction = frag_position - front_face;
	color = vec4(-direction, 1.0);
}