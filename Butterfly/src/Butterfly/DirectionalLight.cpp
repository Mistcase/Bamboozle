#include "Butterfly/butterflypch.h"
#include "DirectionalLight.h"

namespace butterfly
{
    DirectionalLight::DirectionalLight(glm::vec3 intensity, glm::vec3 position, glm::vec3 direction)
        : m_intensity(intensity)
        , m_position(position)
        , m_direction(direction)
    {
    }

    void DirectionalLight::update(float dt)
    {
        // Update position or smth else...
    }

    void DirectionalLight::setIntencity(glm::vec3 intensity)
    {
        m_intensity = intensity;
    }

    void DirectionalLight::setPosition(glm::vec3 position)
    {
        m_position = position;
    }

    void DirectionalLight::setDirection(glm::vec3 direction)
    {
        m_direction = direction;
    }

    glm::vec3 DirectionalLight::getIntensity() const
    {
        return m_intensity;
    }

    glm::vec3 DirectionalLight::getPosition() const
    {
        return m_position;
    }

    glm::vec3 DirectionalLight::getDirection() const
    {
        return m_direction;
    }

} // namespace butterfly
