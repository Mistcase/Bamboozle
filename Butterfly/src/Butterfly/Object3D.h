#pragma once

#include "Butterfly/Core.h"
#include "Butterfly/Renderer/Mesh.h"

#include <filesystem>
#include <glm/glm.hpp>

namespace butterfly
{
	class PerspectiveCamera;

	class Object3D
	{
	public:
		Object3D(const std::filesystem::path& path);
		virtual ~Object3D() = default;

		void setPosition(glm::vec3 position);
		void setRotation(float angle, glm::vec3 axis);
		void setScale(glm::vec3 scale);

		void update(float dt);
		void render() const;

		glm::vec3 getPosition() const;
		glm::vec3 getRotation() const;
		glm::vec3 getScale() const;

		const glm::mat4& getWorldTransform() const;

	private:
		void invalidateTransform();
		void calculateTransform();

	protected:
        Ref<Mesh> m_mesh;
        Material m_material;

	protected:
		glm::mat4 m_transform;
		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };

		bool m_isDirtyTransform = false;
	};
}
