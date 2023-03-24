#include "Object3D.h"

#include "Butterfly/Renderer/Material.h"
#include "Butterfly/Renderer/PerspectiveCamera.h"
#include "Butterfly/Renderer/Renderer.h"
#include "Butterfly/butterflypch.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <fstream>

namespace butterfly
{
    Object3D::Object3D(const std::filesystem::path& path)
        : m_mesh(Mesh::Create(path))
    {
    }

    void Object3D::setMaterial(Ref<Material> material)
    {
        m_material = std::move(material);
    }

    void Object3D::update(float dt)
    {
        Transformable::update();
    }

    void Object3D::render() const
    {
        if (m_material != nullptr)
        {
            m_material->apply();
        }
        static_cast<OpenGLShader*>(Renderer::Shader())->setUniformMat4("u_Transform", m_transform);
        m_mesh->draw();
    }

    Ref<Material> Object3D::getMaterial() const
    {
        return m_material;
    }

} // namespace butterfly
