#include "Butterfly/butterflypch.h"
#include "Renderer.h"

#include "Butterfly/Object3D.h"
#include "Butterfly/Renderer/PerspectiveCamera.h"
#include "Butterfly/Renderer/Renderer2D.h"
#include "Butterfly/Renderer/Shader.h"
#include "Butterfly/Renderer/VertexArray.h"

//Temp
#include "Platform/OpenGL/OpenGLShader.h"

namespace butterfly
{
    const PerspectiveCamera* Renderer::m_camera = nullptr;

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Destroy()
    {
        Renderer2D::Destroy();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(width, height);
    }

    void Renderer::BeginScene(const PerspectiveCamera* camera)
    {
        m_camera = camera;

		const auto& viewProjection = camera->getViewProjection();
		static_cast<OpenGLShader*>(Renderer2D::Shader())->bind();
        static_cast<butterfly::OpenGLShader*>(butterfly::Renderer::Shader())->setUniform3f("u_CameraPosition", m_camera->getPosition());
		static_cast<OpenGLShader*>(Renderer2D::Shader())->setUniformMat4("u_VP", viewProjection);

        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
        RenderCommand::Clear();
    }

    void Renderer::EndScene()
    {
    }

    class Shader* Renderer::Shader()
    {
        return Renderer2D::Shader(); // TODO: Give 3D renderer its own shader
    }

} // namespace butterfly
