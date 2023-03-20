#include "Object3D.h"

#include "Butterfly/Renderer/PerspectiveCamera.h"
#include "Butterfly/Renderer/Mesh.h"

#include <glm/ext/matrix_transform.hpp>
#include <fstream>

namespace butterfly
{
	Object3D::Object3D(const std::filesystem::path& path)
        : m_mesh(Mesh::Create(path))
	{
	}

	void Object3D::setPosition(glm::vec3 position)
	{
		m_transform = glm::translate(glm::mat4(1.0f), position);
	}

	void Object3D::setRotation(float angle, glm::vec3 axis)
	{
        const auto position = glm::vec3(1.0f); // Calculate position from world transform

		m_transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), angle, axis);
	}

	const glm::mat4& Object3D::getWorldTransform() const
	{
		return m_transform;
	}

	void Object3D::draw()
	{
        // Set model matrix
        // m_material->bind();
        m_mesh->draw();
	}
}
