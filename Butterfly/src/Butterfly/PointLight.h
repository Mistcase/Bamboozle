#pragma once

#include <glm/glm.hpp>

namespace butterfly
{
    class PointLight
    {
    public:
        struct Attenuation
        {
            float linearRatio = 1.0f;
            float quadraticRatio = 1.0f;
        };

    public:
        PointLight(glm::vec3 intensity, float radius, glm::vec3 position = glm::vec3{ 0.0f, 0.0f, 0.0f });

        void update(float dt);

        void setPosition(glm::vec3 position);
        void setIntencity(glm::vec3 intensity);
        void setRadius(float radius);
        void setAttenuation(Attenuation attenuation);

        glm::vec3 getPosition() const;
        glm::vec3 getIntensity() const;
        float getRadius() const;
        Attenuation getAttenuation() const;

    private:
        glm::vec3 m_position;
        glm::vec3 m_intensity;
        Attenuation m_attenuation;
        float m_radius;
    };

} // namespace butterfly
