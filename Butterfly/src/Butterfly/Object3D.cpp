#include "Butterfly/butterflypch.h"
#include "Object3D.h"

#include "Butterfly/Renderer/Renderer.h"
#include "Butterfly/Renderer/PerspectiveCamera.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/ext/matrix_transform.hpp>
#include <fstream>

namespace butterfly
{
	Object3D::Object3D(const std::filesystem::path& path)
        : m_mesh(Mesh::Create(path))
	{
		calculateTransform();
	}

	void Object3D::setPosition(glm::vec3 position)
	{
		m_position = position;
		invalidateTransform();
	}

	void Object3D::setRotation(float angle, glm::vec3 axis)
	{
		assert(!"Unsupported");
	}

	void Object3D::setScale(glm::vec3 scale)
	{
		m_scale = scale;
		invalidateTransform();
	}

	const glm::mat4& Object3D::getWorldTransform() const
	{
		return m_transform;
	}

    void Object3D::update(float dt)
    {
		if (m_isDirtyTransform)
		{
			calculateTransform();
		}
    }

	void Object3D::render() const
	{
        // Apply material
		static_cast<OpenGLShader*>(Renderer::Shader())->setUniformMat4("u_Transform", m_transform); // Temp
        m_mesh->draw();
	}

	glm::vec3 Object3D::getPosition() const
	{
		return m_position;
	}

	glm::vec3 Object3D::getRotation() const
	{
		assert(!"");
		return m_rotation;
	}

	glm::vec3 Object3D::getScale() const
	{
		return m_scale;
	}

	void Object3D::invalidateTransform()
	{
		m_isDirtyTransform = true;
	}

	void Object3D::calculateTransform()
	{
		// TODO: Implement rotations
		m_transform = glm::translate(glm::mat4(1.0f), m_position) * glm::scale(glm::mat4(1.0f), m_scale);
		m_isDirtyTransform = false;
	}
}
