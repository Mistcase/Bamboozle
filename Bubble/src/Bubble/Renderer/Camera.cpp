#pragma once

#include "bubblepch.h"
#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace bubble
{
    Camera::Camera(float width, float height)
        : m_projection(glm::ortho(0.0f, width, height, 0.0f, 0.0f, 1000.0f))
    {
        setPosition(glm::vec3(0.0f));
        setRotation(0.0f);
    }

    void Camera::setPosition(const glm::vec3& position)
    {
        const auto transform = glm::translate(glm::mat4(1.0f), position);
        m_view = glm::inverse(transform);
        m_position = position;

        setRotation(m_angle);
        updateViewProjection();
    }

    float Camera::getRotation() const
    {
        return m_angle;
    }

    void Camera::setRotation(float angle)
    {
        m_angle = angle;
        m_rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

        updateViewProjection();
    }

    const glm::vec3& Camera::getPosition() const
    {
        return m_position;
    }

    glm::mat4 Camera::getViewProjection() const
    {
        return m_viewProjection;
    }

    void Camera::updateViewProjection()
    {
        m_viewProjection = m_projection * (m_view * m_rotation);
    }

} // namespace bubble
