@VertexShader
#version 410 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoords;
layout(location = 3) in float a_TexIndex;

uniform mat4 u_VP;

out float v_TexIndex;
out vec2 v_TexCoords;
out vec4 v_Color;

void main()
{
    v_TexIndex = a_TexIndex;
    v_TexCoords = a_TexCoords;
    v_Color = a_Color;

    gl_Position = u_VP * a_Position;
}

@FragmentShader
#version 410 core

layout(location = 0) out vec4 color;

in float v_TexIndex;
in vec2 v_TexCoords;
in vec4 v_Color;

uniform sampler2D u_Textures[16];

void main()
{
    color = texture(u_Textures[int(v_TexIndex)], v_TexCoords) * v_Color;
}
