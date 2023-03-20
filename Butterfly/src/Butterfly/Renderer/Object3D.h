#pragma once

#include "Butterfly/Core.h"
#include <filesystem>
#include <glm/glm.hpp>

namespace butterfly
{
    class Mesh;
    class Material;

	class PerspectiveCamera;

	class Object3D
	{
	public:
		Object3D(const std::filesystem::path& path);
		virtual ~Object3D() = default;

		void setPosition(glm::vec3 position);
		void setRotation(float angle, glm::vec3 axis);

		const glm::mat4& getWorldTransform() const;

		void draw();

	protected:
        Ref<Mesh> m_mesh;
        Ref<Material> m_material;

		glm::mat4 m_transform;
	};
}
