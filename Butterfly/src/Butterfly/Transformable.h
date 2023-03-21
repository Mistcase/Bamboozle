#pragma once

#include <glm/glm.hpp>

namespace butterfly
{
	class Transformable
	{
	public:
		virtual ~Transformable() = default;

		void update();

		void setPosition(glm::vec3 position);
		void setRotation(float angle, glm::vec3 axis);
		void setScale(glm::vec3 scale);

		glm::vec3 getPosition() const;
		glm::vec3 getRotation() const;
		glm::vec3 getScale() const;
		const glm::mat4& getWorldTransform() const;

	protected:
		Transformable();
		virtual void transformChanged();

	private:
		void invalidateTransform();
		void calculateTransform();

	protected:
		glm::mat4 m_transform;
		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };

		bool m_isDirtyTransform = false;
	};

} // namespace butterfly
