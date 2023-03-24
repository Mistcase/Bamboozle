#include "Transformable.h"

#include <glm/ext/matrix_transform.hpp>

namespace butterfly
{
    Transformable::Transformable()
    {
        calculateTransform();
    }

    void Transformable::update()
    {
        if (m_isDirtyTransform)
        {
            calculateTransform();
        }
    }

    void Transformable::setPosition(glm::vec3 position)
    {
        m_position = position;
        invalidateTransform();
    }

    void Transformable::setRotation(glm::quat quaternion)
    {
        m_rotation = quaternion;
        invalidateTransform();
    }

    void Transformable::setRotation(glm::vec3 angles)
    {
        setRotation(glm::quat{ angles });
    }

    void Transformable::setScale(glm::vec3 scale)
    {
        m_scale = scale;
        invalidateTransform();
    }

    const glm::mat4& Transformable::getWorldTransform() const
    {
        return m_transform;
    }

    glm::vec3 Transformable::getPosition() const
    {
        return m_position;
    }

    glm::quat Transformable::getRotation() const
    {
        return m_rotation;
    }

    glm::vec3 Transformable::getScale() const
    {
        return m_scale;
    }

    void Transformable::invalidateTransform()
    {
        m_isDirtyTransform = true;
    }

    void Transformable::calculateTransform()
    {
        m_transform = glm::translate(glm::mat4(1.0f), m_position) * glm::scale(glm::mat4(1.0f), m_scale) * glm::mat4(m_rotation);
        m_isDirtyTransform = false;

        transformChanged();
    }

    void Transformable::transformChanged()
    {
    }

} // namespace butterfly
