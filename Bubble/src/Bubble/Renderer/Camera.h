#pragma once

#include <glm/glm.hpp>

namespace bubble
{
    class Camera
    {
    public:
        Camera(float width, float height);

        const glm::vec3& getPosition() const;
        void setPosition(const glm::vec3& position);

        float getRotation() const;
        void setRotation(float angle);

        glm::mat4 getViewProjection() const;

    private:
        void updateViewProjection();

    private:
        glm::mat4 m_view;
        glm::mat4 m_rotation;
        glm::mat4 m_projection;
        glm::mat4 m_viewProjection;

        glm::vec3 m_position;
        float m_angle = 0.0f;
    };

} // namespace bubble
