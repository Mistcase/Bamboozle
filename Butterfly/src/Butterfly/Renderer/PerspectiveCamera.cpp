#include "PerspectiveCamera.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <stdio.h>

namespace butterfly
{
    PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float zNear, float zFar)
        : m_projection(glm::perspective(fov, aspectRatio, zNear, zFar))
    {
        updateViewProjection();
    }

    void PerspectiveCamera::setViewDirection(glm::vec3 direction)
    {
        m_viewDirection = direction;
        m_isDirtyTransform = true;
    }

    glm::vec3 PerspectiveCamera::getViewDirection() const
    {
        return m_viewDirection;
    }

    const glm::mat4& PerspectiveCamera::getViewProjection() const
    {
        return m_viewProjection;
    }

    void PerspectiveCamera::updateViewProjection()
    {
        const auto right = glm::cross(m_viewDirection, { 0.0f, 1.0f, 0.0f });
        const auto up = glm::cross(right, m_viewDirection);

        m_view = glm::lookAt(m_position, m_position + m_viewDirection, up);
        m_viewProjection = m_projection * m_view;
    }

    void PerspectiveCamera::transformChanged()
    {
        m_viewDirection = glm::rotate(m_rotation, { 0.0f, 0.0f, -1.0f });
        updateViewProjection();
    }

} // namespace butterfly
