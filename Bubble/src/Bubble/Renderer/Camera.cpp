#pragma once

#include "bubblepch.h"
#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace bubble
{
    Camera::Camera(float width, float height)
        : m_projection(glm::ortho(0.0f, width, height, 0.0f, 0.0f, 1.0f))
    {
        setPosition(glm::vec3(0.0f));
        setRotation(0.0f);
    }

    void Camera::setPosition(const glm::vec3& position)
    {
        m_position = position;
        updateViewProjection();
    }

    float Camera::getRotation() const
    {
        return m_rotation;
    }

    void Camera::setRotation(float rotation)
    {   
        m_rotation = rotation;
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
         const auto transform = glm::translate(glm::mat4(1.0f), m_position) *
                    glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));

        m_viewProjection = m_projection * glm::inverse(transform);
    }

} // namespace bubble
