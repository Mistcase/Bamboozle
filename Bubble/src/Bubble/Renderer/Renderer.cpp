#include "bubblepch.h"
#include "Renderer.h"

#include "Bubble/Renderer/Camera.h"
#include "Bubble/Renderer/Shader.h"
#include "Bubble/Renderer/VertexArray.h"

namespace bubble
{
    void Renderer::BeginScene(const Camera* camera, const Shader* shader)
    {
        // BUBBLE_CORE_ASSERT(shader != nullptr);
        shader->bind();

        // Get View * Projection matrix
        // Send it to shader

        shader->setUniformMat4("u_VP", camera->getViewProjection());
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        // Submit to render command queue
        vertexArray->bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

} // namespace bubble
