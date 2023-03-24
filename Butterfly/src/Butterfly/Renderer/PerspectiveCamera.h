#pragma once

#include "Butterfly/Transformable.h"

namespace butterfly
{
    class PerspectiveCamera : public Transformable
    {
    public:
        PerspectiveCamera(float fov, float aspectRatio, float zNear, float zFar);

        void setViewDirection(glm::vec3 direction);

        glm::vec3 getViewDirection() const;
        const glm::mat4& getViewProjection() const;

    private:
        void updateViewProjection();
        void transformChanged() override;

    private:
        glm::mat4 m_view;
        glm::mat4 m_projection;
        glm::mat4 m_viewProjection;

        glm::vec3 m_viewDirection = { 0.0f, 0.0f, -1.0f };
    };

} // namespace butterfly
