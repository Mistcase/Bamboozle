#include "bubblepch.h"
#include "Renderer.h"

#include "Bubble/Renderer/VertexArray.h"

namespace bubble
{
    void Renderer::BeginScene()
    {
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
