#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main()
{
	fragColor = inColor;
	fragTexCoord = inTexCoord;

    gl_Position = vec4(position.xy, position.z, 1.0f);
}
