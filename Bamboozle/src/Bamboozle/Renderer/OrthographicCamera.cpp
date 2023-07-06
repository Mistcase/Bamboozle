#include "OrthographicCamera.h"

#include "Bamboozle/bbzl.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

// TODO: optimize code

namespace bbzl
{
    OrthographicCamera::OrthographicCamera(float width, float height)
        : m_projection(glm::ortho(-0.5f * width, 0.5f * width, -0.5f * height, 0.5f * height, 0.0f, 1.0f))
        , m_width(width)
        , m_height(height)
    {
        setPosition(glm::vec3(0.0f));
        setRotation(0.0f);
    }

    void OrthographicCamera::setSize(float width, float height)
    {
        m_width = width;
        m_height = height;

        setZoom(m_zoom);

        updateViewProjection();
    }

    void OrthographicCamera::setPosition(const glm::vec3& position)
    {
        m_position = position;
        updateViewProjection();
    }

    float OrthographicCamera::getRotation() const
    {
        return m_rotation;
    }

    void OrthographicCamera::setRotation(float rotation)
    {
        m_rotation = rotation;
        updateViewProjection();
    }

    float OrthographicCamera::getZoom() const
    {
        return m_zoom;
    }

    void OrthographicCamera::setZoom(float zoom)
    {
        const auto dw = 0.5f * m_width;
        const auto dh = 0.5f * m_height;

        m_zoom = zoom;
        m_projection = glm::ortho(-dw * m_zoom, dw * m_zoom, -dh * m_zoom, dh * m_zoom, 0.0f, 1.0f);
        updateViewProjection();
    }

    const glm::vec3& OrthographicCamera::getPosition() const
    {
        return m_position;
    }

    glm::mat4 OrthographicCamera::getViewProjection() const
    {
        return m_viewProjection;
    }

    void OrthographicCamera::updateViewProjection()
    {
        const auto transform = glm::translate(glm::mat4(1.0f), m_position) * glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));

        m_viewProjection = m_projection * glm::inverse(transform);
    }

} // namespace bbzl
