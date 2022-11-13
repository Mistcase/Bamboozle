#include "bubblepch.h"
#include "Renderer.h"

#include "Bubble/Renderer/Camera.h"
#include "Bubble/Renderer/Shader.h"
#include "Bubble/Renderer/VertexArray.h"

//Temp
#include "Platform/OpenGL/OpenGLShader.h"

namespace bubble
{
    const Camera* Renderer::m_camera = nullptr;

    void Renderer::Init()
    {
        RenderCommand::Init();
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
        BUBBLE_CORE_ASSERT(shader != nullptr, "Shader is nullptr");

        shader->bind();
        static_cast<const bubble::OpenGLShader*>(shader)->setUniformMat4("u_VP", m_camera->getViewProjection());
        static_cast<const bubble::OpenGLShader*>(shader)->setUniformMat4("u_Transform", transform);

        // Submit to render command queue
        vertexArray->bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

} // namespace bubble
