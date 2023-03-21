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

		const glm::mat4& getWorldTransform() const;

        void update(float dt);
		void render() const;

	protected:
        Ref<Mesh> m_mesh;
        Material m_material;

		glm::mat4 m_transform;
	};
}
