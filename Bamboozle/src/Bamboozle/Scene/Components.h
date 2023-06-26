#pragma once

#include "Bamboozle/Core.h"

#include <glm/glm.hpp>
#include <string>

namespace bbzl
{
    struct TagComponent
    {
        std::string tag;
    };

    struct CameraComponent
    {
        glm::mat4 projection;
		glm::vec3 viewDirection;
    };

    struct DirectionalLightComponent
    {
        glm::vec3 intensity;
        glm::vec3 direction;
    };

    struct PointLightComponent
    {
        PointLightComponent(const glm::vec3& _intencity, float _radius)
            : intensity(_intencity)
            , radius(_radius)
        {
        }

        struct Attenuation
        {
            float linearRatio = 1.0f;
            float quadraticRatio = 1.0f;
        };

        glm::vec3 intensity;
        Attenuation attenuation;
        float radius;
    };

    struct Texture2D;
    struct Texture2DComponent
    {
        Ref<Texture2D> texture;
    };

} // namespace bbzl
