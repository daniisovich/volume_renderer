#version 460 core

in vec3 frag_position;
out vec4 color;

uniform float num_samples;
uniform float smooth_step_start;
uniform float smooth_step_end;

layout (binding = 0) uniform sampler2D front_faces;
layout (binding = 1) uniform sampler3D volume;


bool inVolume(vec3 volume_position) {
	return volume_position.x >= 0.0f && volume_position.x <= 1.0f &&
		   volume_position.y >= 0.0f && volume_position.y <= 1.0f &&
		   volume_position.z >= 0.0f && volume_position.z <= 1.0f;
}

void main() {

	vec3 volume_position = texelFetch(front_faces, ivec2(gl_FragCoord), 0).xyz;
	vec3 step = normalize(frag_position - volume_position) / num_samples;

	color = vec4(0.0f);
	while(inVolume(volume_position)) {

		float volume_value = texture(volume, volume_position).r;
		vec4 volume_color = vec4(smoothstep(smooth_step_start, smooth_step_end, volume_value));

		color.rgb = color.rgb + (1.0f - color.a) * volume_color.a * volume_color.rgb;
		color.a   = color.a   + (1.0f - color.a) * volume_color.a;

		if (color.a > 0.95)
			break;

		volume_position += step;
	}

}