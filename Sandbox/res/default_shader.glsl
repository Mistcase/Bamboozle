@VertexShader
#version 410 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoords;
layout(location = 3) in int a_TexIndex;

flat out int v_TexIndex;
out vec2 v_TexCoords;
out vec4 v_Color;

void main()
{
    v_TexCoords = a_TexCoords;
	v_Color = a_Color;
	v_TexIndex = a_TexIndex;

	gl_Position = a_Position;
}

@FragmentShader
#version 410 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoords;
flat in int v_TexIndex;

uniform sampler2D u_Textures[16];

void main()
{
	vec3 textureColor = texture(u_Textures[v_TexIndex], v_TexCoords).rgb;
	color = vec4(textureColor, 1.0f);
}
