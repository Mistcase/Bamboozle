#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace bbzl
{
    class TransformComponent final
    {
    public:
        TransformComponent();

        void updateWorldTransform();

        void setPosition(glm::vec3 position);
        void setRotation(glm::quat quaternion);
        void setRotation(glm::vec3 angles);
        void setScale(glm::vec3 scale);

        glm::vec3 getPosition() const;
        glm::quat getRotation() const;
        glm::vec3 getScale() const;
        const glm::mat4& getWorldTransform() const;

    private:
        void invalidateTransform();
        void calculateTransform();

    private:
        glm::mat4 m_transform;
        glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
        glm::quat m_rotation = glm::identity<glm::quat>();
        glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };

        bool m_isDirtyTransform = false;
    };

} // namespace bbzl
