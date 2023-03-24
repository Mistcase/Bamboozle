#include "PointLight.h"

#include "Butterfly/butterflypch.h"

namespace butterfly
{
    PointLight::PointLight(glm::vec3 intensity, float radius, glm::vec3 position)
        : m_intensity(intensity)
        , m_position(position)
    {
    }

    void PointLight::update(float dt)
    {
    }

    void PointLight::setIntencity(glm::vec3 intensity)
    {
        m_intensity = intensity;
    }

    void PointLight::setPosition(glm::vec3 position)
    {
        m_position = position;
    }

    void PointLight::setRadius(float radius)
    {
        m_radius = radius;
    }

    void PointLight::setAttenuation(Attenuation attenuation)
    {
        m_attenuation = attenuation;
    }

    glm::vec3 PointLight::getIntensity() const
    {
        return m_intensity;
    }

    glm::vec3 PointLight::getPosition() const
    {
        return m_position;
    }

    float PointLight::getRadius() const
    {
        return m_radius;
    }

    PointLight::Attenuation PointLight::getAttenuation() const
    {
        return m_attenuation;
    }

} // namespace butterfly
