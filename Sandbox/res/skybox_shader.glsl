@VertexShader
#version 410 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec3 a_Normal;
layout(location = 3) in vec2 a_TexCoords;

uniform mat4 u_Transform;
uniform mat4 u_VP;

out vec2 v_TexCoords;

void main()
{
    v_TexCoords = a_TexCoords;
    gl_Position = u_VP * u_Transform * a_Position;
}

@FragmentShader
#version 410 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoords;

uniform sampler2D u_SkyBox;

void main()
{
	color = texture(u_SkyBox, v_TexCoords);
}
