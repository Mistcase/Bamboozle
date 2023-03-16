#include "PerspectiveCamera.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#include <stdio.h>

namespace butterfly
{
	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float zNear, float zFar)
		: m_projection(glm::perspective(fov, aspectRatio, zNear, zFar))
	{
		setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	}

	const glm::vec3& PerspectiveCamera::getPosition() const
	{
		return m_position;
	}

	void PerspectiveCamera::setPosition(const glm::vec3& position)
	{
		m_position = position;
		updateViewProjection();
	}

	glm::mat4 PerspectiveCamera::getViewProjection() const
	{
		return m_viewProjection;
	}

	void PerspectiveCamera::updateViewProjection()
	{
		m_view = glm::lookAt(m_position, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
		// m_viewProjection = m_projection * glm::inverse(m_view);
		m_viewProjection = m_projection * m_view;
	}

} // namespace butterfly
