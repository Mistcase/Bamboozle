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
out vec3 v_PositionWorldSpace;

uniform vec3 u_CameraPosition;

void main()
{
    vec4 position = u_Transform * a_Position;

    v_TexCoords = a_TexCoords;
	v_Color = a_Color;
	v_Normal = a_Normal;
    v_DirectionToCamera = normalize(position.xyz - u_CameraPosition);
    v_PositionWorldSpace = position.xyz;

    gl_Position = u_VP * position;
}

@FragmentShader
#version 410 core

layout(location = 0) out vec4 color;

//in float v_TexIndex;
in vec2 v_TexCoords;
in vec4 v_Color;
in vec3 v_Normal;
in vec3 v_DirectionToCamera;
in vec3 v_PositionWorldSpace;

// Lights
struct PointLight
{
    vec3 position; //  0
    vec3 intensity; // 16
    float radius;   // 28
    float attenuationRatioLinear; // 32
    float attenuationRatioQuadratic; // 36
}; // 40 bytes

layout (std140) uniform PointLights
{
    uint usedPointLights;
    PointLight lights[8]; // Max 8 lights sumultaniously
};

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
    vec3 textureColor = vec3(0.0f);
    if (textureDefault != -1)
	{
		textureColor = texture(u_Textures[textureDefault], v_TexCoords).rgb;
	}

    color = vec4(0.0f);
    for (uint i = 0; i < usedPointLights; i++)
    {
        PointLight light = lights[i];

        // Ambient light
        vec3 ambientLight = light.intensity * ka * textureColor;

        // Diffuse light
        float distanceToLight = length(v_PositionWorldSpace - light.position);
        float fade = max(distanceToLight - light.radius, 0.0f);
        float attenuation = 1.0f + light.attenuationRatioLinear * fade + light.attenuationRatioQuadratic * fade * fade;

        vec3 lightDirection = normalize(light.position - v_PositionWorldSpace);
        vec3 diffuseLight = (light.intensity * kd * max(dot(lightDirection, v_Normal), 0.0f)) / attenuation;

        // Specular light
        vec3 reflectedLight = reflect(lightDirection, v_Normal);
        vec3 specularLight = (light.intensity * ks * pow(max(dot(reflectedLight, v_DirectionToCamera), 0.0f), sa)) / attenuation;

        color += vec4(ambientLight + diffuseLight + specularLight, 1.0f);
    }
}
