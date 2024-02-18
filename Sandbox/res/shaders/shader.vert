#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

layout(push_constant) uniform Push {
	mat2 transform;
	vec2 offset;
	vec3 color;
} push;

void main()
{
    gl_Position = vec4(push.offset + push.transform * position.xy, position.z, 1.0f);
}
