#include "Skybox.h"

// #include "Bamboozle/Scene/Scene.h"

#include "Bamboozle/Renderer/PerspectiveCamera.h"
#include "Bamboozle/Renderer/Renderer.h"
#include "Bamboozle/Renderer/Shader.h"
#include "Bamboozle/Renderer/Texture.h"
#include "Bamboozle/bbzl.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace
{
    std::unique_ptr<bbzl::Shader> skyboxShader;

} // namespace

namespace bbzl
{
    SkyBox::SkyBox(const std::filesystem::path& sphere, const std::filesystem::path& texture, const PerspectiveCamera* camera)
        : m_texture(Texture2D::Create(texture.generic_string()))
        , m_camera(camera)
    {
        assert(m_camera != nullptr);
        assert(m_texture != nullptr);
    }

    // void SkyBox::render() const
    // {
    //     Renderer::SkyboxShader()->bind();

    //     static_cast<OpenGLShader*>(Renderer::SkyboxShader())->setUniformMat4("u_Transform", m_transform);
    //     static_cast<OpenGLShader*>(Renderer::SkyboxShader())->setUniformMat4("u_VP", m_camera->getViewProjection());
    //     static_cast<OpenGLShader*>(Renderer::SkyboxShader())->setUniform1i("u_SkyBox", 0);

    //     m_texture->bind(0);
    //     m_mesh->draw();

    //     Renderer::Shader()->bind();
    // }

} // namespace bbzl
