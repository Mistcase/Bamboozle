#include "Transformable.h"

#include <glm/ext/matrix_transform.hpp>

namespace butterfly
{
    TransformComponent::TransformComponent()
    {
        calculateTransform();
    }

    void TransformComponent::updateWorldTransform()
    {
        if (m_isDirtyTransform)
        {
            calculateTransform();
        }
    }

    void TransformComponent::setPosition(glm::vec3 position)
    {
        m_position = position;
        invalidateTransform();
    }

    void TransformComponent::setRotation(glm::quat quaternion)
    {
        m_rotation = quaternion;
        invalidateTransform();
    }

    void TransformComponent::setRotation(glm::vec3 angles)
    {
        setRotation(glm::quat{ angles });
    }

    void TransformComponent::setScale(glm::vec3 scale)
    {
        m_scale = scale;
        invalidateTransform();
    }

    const glm::mat4& TransformComponent::getWorldTransform() const
    {
        return m_transform;
    }

    glm::vec3 TransformComponent::getPosition() const
    {
        return m_position;
    }

    glm::quat TransformComponent::getRotation() const
    {
        return m_rotation;
    }

    glm::vec3 TransformComponent::getScale() const
    {
        return m_scale;
    }

    void TransformComponent::invalidateTransform()
    {
        m_isDirtyTransform = true;
    }

    void TransformComponent::calculateTransform()
    {
        m_transform = glm::translate(glm::mat4(1.0f), m_position) * glm::scale(glm::mat4(1.0f), m_scale) * glm::mat4(m_rotation);
        m_isDirtyTransform = false;
    }

} // namespace butterfly
