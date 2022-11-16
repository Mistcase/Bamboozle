#pragma once

#include <glm/glm.hpp>

namespace bubble
{
    class Camera
    {
    public:
        Camera(float width, float height);
        void setSize(float width, float height);

        const glm::vec3& getPosition() const;
        void setPosition(const glm::vec3& position);

        float getRotation() const;
        void setRotation(float rotation);

        float getZoom() const;
        void setZoom(float zoom);

        glm::mat4 getViewProjection() const;

    private:
        void updateViewProjection();

    private:
        glm::mat4 m_projection;

    private:
        glm::mat4 m_viewProjection;
        float m_width;
        float m_height;

        glm::vec3 m_position;
        float m_rotation = 0.0f;
        float m_zoom = 1.0f;
    };

} // namespace bubble
