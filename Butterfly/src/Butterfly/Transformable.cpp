#include "Transformable.h"

#include <glm/ext/matrix_transform.hpp>

namespace butterfly
{
	Transformable::Transformable()
	{
		calculateTransform();
	}

	void Transformable::update()
	{
		if (m_isDirtyTransform)
		{
			calculateTransform();
		}
	}

	void Transformable::setPosition(glm::vec3 position)
	{
		m_position = position;
		invalidateTransform();
	}

	void Transformable::setRotation(float angle, glm::vec3 axis)
	{
		assert(!"Unsupported");
	}

	void Transformable::setScale(glm::vec3 scale)
	{
		m_scale = scale;
		invalidateTransform();
	}

	const glm::mat4& Transformable::getWorldTransform() const
	{
		return m_transform;
	}

	glm::vec3 Transformable::getPosition() const
	{
		return m_position;
	}

	glm::vec3 Transformable::getRotation() const
	{
		assert(!"");
		return m_rotation;
	}

	glm::vec3 Transformable::getScale() const
	{
		return m_scale;
	}

	void Transformable::invalidateTransform()
	{
		m_isDirtyTransform = true;
	}

	void Transformable::calculateTransform()
	{
		// TODO: Implement rotations
		m_transform = glm::translate(glm::mat4(1.0f), m_position) * glm::scale(glm::mat4(1.0f), m_scale);
		m_isDirtyTransform = false;

		transformChanged();
	}

	void Transformable::transformChanged()
	{
	}

} // namespace butterfly
