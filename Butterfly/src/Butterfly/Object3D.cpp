#include "Butterfly/butterflypch.h"
#include "Object3D.h"

#include "Butterfly/Renderer/Renderer.h"
#include "Butterfly/Renderer/PerspectiveCamera.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>

namespace butterfly
{
	Object3D::Object3D(const std::filesystem::path& path)
        : m_mesh(Mesh::Create(path))
	{
	}

    void Object3D::update(float dt)
    {
		Transformable::update();
    }

	void Object3D::render() const
	{
        // Apply material
		static_cast<OpenGLShader*>(Renderer::Shader())->setUniformMat4("u_Transform", m_transform); // Temp
        m_mesh->draw();
	}

}
