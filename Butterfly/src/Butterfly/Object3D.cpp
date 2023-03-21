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
	}

	void Object3D::setPosition(glm::vec3 position)
	{
		m_transform = glm::translate(glm::mat4(1.0f), position);
	}

	void Object3D::setRotation(float angle, glm::vec3 axis)
	{
        const auto position = glm::vec3(0.0f, 0.0f, 0.0f); // TODO: Calculate position from world transform

		m_transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), angle, axis);
	}

	void Object3D::setScale(glm::vec3 scale)
	{
		const auto position = glm::vec3(0.0f, 0.0f, 0.0f); // TODO: Calculate position from world transform

		m_transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), scale);
	}

	const glm::mat4& Object3D::getWorldTransform() const
	{
		return m_transform;
	}

    void Object3D::update(float dt)
    {
    }

	void Object3D::render() const
	{
        // m_material->bind();
        //static_cast<OpenGLShader*>(Renderer::SkyboxShader())->setUniformMat4("u_Transform", m_transform); // Temp
		static_cast<OpenGLShader*>(Renderer::Shader())->setUniformMat4("u_Transform", m_transform); // Temp
        m_mesh->draw();
	}
}
