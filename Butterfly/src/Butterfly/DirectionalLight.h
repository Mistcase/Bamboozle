#pragma once

#include <glm/glm.hpp>

namespace butterfly
{
    class DirectionalLight
    {
    public:
        DirectionalLight(glm::vec3 intensity, glm::vec3 position, glm::vec3 direction);

        void update(float dt);

        void setIntencity(glm::vec3 intensity);
        void setPosition(glm::vec3 position);
        void setDirection(glm::vec3 direction);

        glm::vec3 getIntensity() const;
        glm::vec3 getPosition() const;
        glm::vec3 getDirection() const;

    private:
        glm::vec3 m_intensity;
        glm::vec3 m_position;
        glm::vec3 m_direction;
    };

} // namespace butterfly
