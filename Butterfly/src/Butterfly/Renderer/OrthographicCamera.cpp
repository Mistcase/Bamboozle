#include "OrthographicCamera.h"

#include "Butterfly/butterflypch.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

// TODO: optimize code

namespace butterfly
{
    Camera::Camera(float width, float height)
        : m_projection(glm::ortho(-0.5f * width, 0.5f * width, -0.5f * height, 0.5f * height, 0.0f, 1.0f))
        , m_width(width)
        , m_height(height)
    {
        setPosition(glm::vec3(0.0f));
        setRotation(0.0f);
    }

    void Camera::setSize(float width, float height)
    {
        m_width = width;
        m_height = height;

        setZoom(m_zoom);

        updateViewProjection();
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

    float Camera::getZoom() const
    {
        return m_zoom;
    }

    void Camera::setZoom(float zoom)
    {
        const auto dw = 0.5f * m_width;
        const auto dh = 0.5f * m_height;

        m_zoom = zoom;
        m_projection = glm::ortho(-dw * m_zoom, dw * m_zoom, -dh * m_zoom, dh * m_zoom, 0.0f, 1.0f);
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
        const auto transform = glm::translate(glm::mat4(1.0f), m_position) * glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));

        m_viewProjection = m_projection * glm::inverse(transform);
    }

} // namespace butterfly
