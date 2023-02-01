#include "Butterfly/butterflypch.h"
#include "Renderer.h"

#include "Butterfly/Renderer/Camera.h"
#include "Butterfly/Renderer/Renderer2D.h"
#include "Butterfly/Renderer/Shader.h"
#include "Butterfly/Renderer/VertexArray.h"

//Temp
#include "Platform/OpenGL/OpenGLShader.h"

namespace butterfly
{
    const Camera* Renderer::m_camera = nullptr;

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

    void Renderer::BeginScene(const Camera* camera)
    {
        m_camera = camera;
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const Shader* shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        BUTTERFLY_CORE_ASSERT(shader != nullptr, "Shader is nullptr");

        shader->bind();
        static_cast<const butterfly::OpenGLShader*>(shader)->setUniformMat4("u_VP", m_camera->getViewProjection());
        static_cast<const butterfly::OpenGLShader*>(shader)->setUniformMat4("u_Transform", transform);

        // Submit to render command queue
        vertexArray->bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

} // namespace butterfly
