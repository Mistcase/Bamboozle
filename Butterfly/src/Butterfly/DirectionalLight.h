#pragma once

#include <glm/glm.hpp>

namespace butterfly
{
    class DirectionalLight
    {
    public:
        DirectionalLight(glm::vec3 intensity, glm::vec3 direction);

		void setIntensity(glm::vec3 intensity);
		void setDirection(glm::vec3 direction);

		virtual void update(float dt);

		glm::vec3 getIntensity() const;
		glm::vec3 getDirection() const;

    private:
		glm::vec3 m_intensity;
		glm::vec3 m_direction;
    };

} // namespace butterfly
