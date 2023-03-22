@VertexShader
#version 410 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_Transform;
uniform mat4 u_VP;

out vec4 v_Color;

void main()
{
    v_Color = a_Color;
    gl_Position = u_VP * u_Transform * a_Position;
}

@FragmentShader
#version 410 core

layout(location = 0) out vec4 color;

in vec4 v_Color;

void main()
{
	color = v_Color;
}
