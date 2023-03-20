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
out vec3 v_DirectionToCamera;

uniform vec3 u_cameraPosition;

void main()
{
    v_TexCoords = a_TexCoords;
	v_Color = a_Color;
	v_Normal = a_Normal;
    v_DirectionToCamera = normalize(a_Position.xyz - u_cameraPosition);

    gl_Position = u_VP * a_Position;
}

@FragmentShader
#version 410 core

layout(location = 0) out vec4 color;

//in float v_TexIndex;
in vec2 v_TexCoords;
in vec4 v_Color;
in vec3 v_Normal;
in vec3 v_DirectionToCamera;

uniform vec3 u_lightDirection;

// Intencites
uniform vec3 u_ia;
uniform vec3 u_id;
uniform vec3 u_is;

// Material attributes
uniform float u_ka;
uniform float u_kd;
uniform float u_ks;
uniform float u_a;

void main()
{
	vec3 ambientLight = u_ia * u_ka;
	vec3 diffuseLight = u_id * u_kd * max(dot(u_lightDirection, v_Normal), 0.0f);

    vec3 reflectedLight = reflect(u_lightDirection, v_Normal);
    vec3 specularLight = u_is * u_ks * pow(max(dot(reflectedLight, v_DirectionToCamera), 0.0f), u_a);

    color = vec4(ambientLight + diffuseLight + specularLight, 1.0f);
}
