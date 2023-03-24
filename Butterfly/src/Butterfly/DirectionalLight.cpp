#include "DirectionalLight.h"

namespace butterfly
{
    DirectionalLight::DirectionalLight(glm::vec3 intensity, glm::vec3 direction)
        : m_intensity(intensity)
        , m_direction(direction)
    {
    }

    void DirectionalLight::setIntensity(glm::vec3 intensity)
    {
        m_intensity = intensity;
    }

    void DirectionalLight::setDirection(glm::vec3 direction)
    {
        m_direction = direction;
    }

    void DirectionalLight::update(float dt)
    {
    }

    glm::vec3 DirectionalLight::getIntensity() const
    {
        return m_intensity;
    }

    glm::vec3 DirectionalLight::getDirection() const
    {
        return m_direction;
    }

} // namespace butterfly
