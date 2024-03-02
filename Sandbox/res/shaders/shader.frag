#version 450

layout (location = 0) in vec3 color;
layout(location = 1) in vec2 fragTexCoord;

layout(set = 0, binding = 0) uniform UniformBufferObject { 
	mat4 model;
	mat4 view;
	mat4 proj;
} ubo;

layout(set = 0, binding = 1) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;

void main()
{
	outColor = texture(texSampler, fragTexCoord);
}