@VertexShader
#version 410 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec3 a_Normal;
layout(location = 3) in vec2 a_TexCoords;

uniform mat4 u_VP;

//out float v_TexIndex;
out vec2 v_TexCoords;
out vec4 v_Color;
out vec3 v_Normal;

void main()
{
    v_TexCoords = a_TexCoords;
	v_Color = a_Color;
	v_Normal = a_Normal;

    gl_Position = u_VP * a_Position;
}

@FragmentShader
#version 410 core

layout(location = 0) out vec4 color;

//in float v_TexIndex;
in vec2 v_TexCoords;
in vec4 v_Color;
in vec3 v_Normal;

uniform vec3 u_lightDirection;
uniform vec3 u_ambientColor;
uniform float u_ka;
uniform float u_kd;

uniform sampler2D u_Textures[16];

void main()
{
    // color = texture(u_Textures[int(v_TexIndex)], v_TexCoords) * v_Color;
	vec3 ambientLight = u_ambientColor * u_ka;
	vec3 diffuseLight = v_Color.rgb * u_kd * max(dot(u_lightDirection, v_Normal), 0.0f);

	color = vec4(ambientLight + diffuseLight, 1.0f);
}
