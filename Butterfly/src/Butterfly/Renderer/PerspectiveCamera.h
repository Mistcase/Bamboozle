#pragma once

#include <glm/glm.hpp>

namespace butterfly
{
	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float fov, float aspectRatio, float zNear, float zFar);

		const glm::vec3& getPosition() const;
		void setPosition(const glm::vec3& position);

		glm::mat4 getViewProjection() const;

	private:
		void updateViewProjection();

	private:
		glm::mat4 m_view;
		glm::mat4 m_projection;
		glm::mat4 m_viewProjection;

	private:
		glm::vec3 m_position;
	};

} // namespace butterfly
