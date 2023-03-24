@VertexShader
#version 410 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec3 a_Normal;
layout(location = 3) in vec2 a_TexCoords;

uniform mat4 u_Transform;
uniform mat4 u_VP;

//out float v_TexIndex;
out vec2 v_TexCoords;
out vec4 v_Color;
out vec3 v_Normal;
out vec3 v_DirectionToCamera;

uniform vec3 u_CameraPosition;

void main()
{
    v_TexCoords = a_TexCoords;
	v_Color = a_Color;
	v_Normal = a_Normal;
    v_DirectionToCamera = normalize(a_Position.xyz - u_CameraPosition);

    gl_Position = u_VP * u_Transform * a_Position;
}

@FragmentShader
#version 410 core

struct DirectionalLight
{
    vec3 intensity;
    vec3 position;
    vec3 direction;
};

layout(location = 0) out vec4 color;

//in float v_TexIndex;
in vec2 v_TexCoords;
in vec4 v_Color;
in vec3 v_Normal;
in vec3 v_DirectionToCamera;

// Lights
uniform int u_DirectionalLightCount;
uniform DirectionalLight u_DirectionalLights[64];

// Material attributes
layout (std140) uniform Material
{
	float ka;
	float kd;
	float ks;
	float sa;

	int textureDefault;
	int textureSpecularMap;
};

uniform sampler2D u_Textures[16];

void main()
{
    color = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    for (int i = 0; i < u_DirectionalLightCount; i++)
    {
        DirectionalLight light = u_DirectionalLights[i];

        vec3 ambientLight = light.intensity * ka;
        vec3 diffuseLight = light.intensity * kd * max(dot(light.direction, v_Normal), 0.0f);

        vec3 reflectedLight = reflect(light.direction, v_Normal);
        vec3 specularLight = light.intensity * ks * pow(max(dot(reflectedLight, v_DirectionToCamera), 0.0f), sa);

        color.rgb += ambientLight + diffuseLight + specularLight;
    }

	if (textureDefault != -1)
	{
		color += texture(u_Textures[textureDefault], v_TexCoords);
	}
}
